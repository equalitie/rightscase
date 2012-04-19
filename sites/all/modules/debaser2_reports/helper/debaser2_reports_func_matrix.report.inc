<?php

/*
 all post variable processing happens here
 processing the post variables should return a function to be used and arguments to be passed to that function
*/
function debaser2_reports_select_single_query_function( $post, $func_type ){
  //matrix of graph functions - outer indexes relate to violation filter
  // inner are for actor filter
  //todo create list of variables in comments
  
  foreach($post as $key => $variable){
    $$key = $variable;
  }
  // ACTOR STATS
  if( isset( $field_type ) ){
    return array(
      'func' => debaser2_reports_actor_functions( $field_type, $actor_type, $func_type ),
      'arg' => $actor_type
    );
  }
  //CASE STATS
  if( isset( $case_options ) ){
    // dpm($case_filters);
    $case_query = array();
    $filter_type = '';
    
    if( $case_location_options ) {
      $filter_type = 'location';
      $case_query['arg'] = $case_location_options;
    }
    if( $case_status_options ){
      $filter_type = 'status';
      $case_query['arg'] = $case_status_options;
    }

    if( !$case_location_options && !$case_status_options) {
       $filter_type = 'status';
       $case_query['arg'] = NULL;
    }

    $case_query['func'] = debaser2_reports_case_functions( $case_options, $filter_type, $func_type );
    
    return $case_query;
  }

  //VIOLATION STATS
  if( isset( $violation_options ) ){
    $vioflag =  ( isset( $violation_location_options ) && !$violation_location_options === 0  ) ? 'location' : 'nolocation';
    return array(
      'func' => debaser2_reports_violation_functions( $violation_options, $vioflag, $func_type ),
      'arg' => $violation_location_options,
      );
  }

  //VICTIM vs VIOLATION STATS
  //todo add argument if there is a date attached
  if( isset( $violation_victim_options ) ){
    // dpm( $post );
    return array(
      'func' => debaser2_reports_victims_functions( $violation_victim_options, $violation_actor_options, $func_type ),
      'arg' => ( isset( $int_standard ) ) ? $int_standard : $violation_actor_options,
    );
  }
  //new statistics
  //todo add new form processing
  
  // POLITICAL AFFILIATION
  if( isset( $political_affiliation_options ) ){
    return array(
      'func' => debaser2_reports_victims_functions( 'political_affiliation', $political_affiliation_options, $func_type ),
      'arg' => ( isset( $political_affiliation )   && $political_affiliation != '0') ? $political_affiliation : NULL,
    );
  }
  
  // OTHERS
  if( isset( $other_statistics ) ){
    return array(
      'func' => debaser2_reports_victims_functions( 'others', $other_statistics, $func_type ),
      'arg' => NULL,
    );
  }
  
  
}

/**
 * matrix of functions to display syayistics for actors alone
 */
function debaser2_reports_actor_functions( $field_type, $actor_type, $func_type ){
  $type_single = array(//type
      'query' => 'debaser2_reports_query_actor_type',
      'format' => 'debaser2_reports_prepare_single_array',
      'display' => 'debaser2_reports_graph_actor_type'
    );

  $gender_single = array(//gender
      'query' => 'debaser2_reports_query_actor_gender',
      'format' => 'debaser2_reports_prepare_single_array',
      'display' => 'debaser2_reports_graph_actor_type_gender'
    );

  $gender_multiple = array(//gender
      'query' => 'debaser2_reports_query_actor_gender',
      'format' => 'debaser2_reports_prepare_multiple_array',
      'display' => 'debaser2_reports_graph_actor_type_gender_multiple'
    );

  $ethnicity_single = array(//gender
      'query' => 'debaser2_reports_query_actor_ethnicity',
      'format' => 'debaser2_reports_prepare_single_array',
      'display' => 'debaser2_reports_graph_actor_type_ethnicity'
    );

  $ethnicity_multiple = array(//gender
      'query' => 'debaser2_reports_query_actor_ethnicity',
      'format' => 'debaser2_reports_prepare_multiple_array',
      'display' => 'debaser2_reports_graph_actor_type_ethnicity_multiple'
    );

  $political_single = array(//gender
      'query' => 'debaser2_reports_query_actor_political_affiliation',
      'format' => 'debaser2_reports_prepare_single_array',
      'display' => 'debaser2_reports_graph_actor_type_political'
    );

  $political_multiple = array(//gender
      'query' => 'debaser2_reports_query_actor_political_affiliation',
      'format' => 'debaser2_reports_prepare_multiple_array',
      'display' => 'debaser2_reports_graph_actor_type_political_multiple'
    );

  $age_single = array(//gender
      'query' => 'debaser2_reports_query_actor_age',
      'format' => 'debaser2_reports_prepare_single_array',
      'display' => 'debaser2_reports_graph_actor_type_age'
    );

  $age_multiple = array(//gender
      'query' => 'debaser2_reports_query_actor_age',
      'format' => 'debaser2_reports_prepare_multiple_array',
      'display' => 'debaser2_reports_graph_actor_type_age_multiple'
    );

  $query_functions = array(
    1 => array( //type
      0=> $type_single,
      1=> $type_single,
      2=> $type_single,
      3=> $type_single,
    ),
    2 => array( // gender
      0 => $gender_multiple,
      1 => $gender_single,
      2 => $gender_single,
      3 => $gender_single,
    ),
    3 => array( // ethnicity
      0 => $ethnicity_multiple,
      1 => $ethnicity_single,
      2 => $ethnicity_single,
      3 => $ethnicity_single,
    ),
    4 => array( // political_affiliations
      0 => $political_multiple,
      1 => $political_single,
      2 => $political_single,
      3 => $political_single,
    ),
    5 => array( // age
      0 => $age_multiple,
      1 => $age_single,
      2 => $age_single,
      3 => $age_single,
    ),
    /*
    6 => array(
      'query' => 'debaser2_reports_query_actor_perpetrator_gender_political_affiliation',
      'format' => '',
      'display' => ''
    ),
    7 => array(
      'query' => 'debaser2_reports_query_actor_ehnicity_political_affiliation',
      'format' => '',
      'display' => ''
    ),
    8 => array(
      'query' => 'debaser2_reports_query_actor_age_perpetrator',
      'format' => '',
      'display' => ''
    ),
    */
  );

  return $query_functions[$field_type][$actor_type][$func_type];
}


function debaser2_reports_case_functions( $field_type, $filter_type, $func_type ){
  $query_functions = array(
    1 => array( // status
      'status' => array(
        'query' => 'debaser2_reports_query_case_status_status',
        // 'format' => 'debaser2_prepare_single_array_alt',
        'format' => 'debaser2_reports_prepare_single_array',
        'display' => 'debaser2_reports_graph_case_status_status'
      ),
      'location' => array(
        'query' => 'debaser2_reports_query_case_status_location',
        'format' => 'debaser2_reports_prepare_single_array',
        'display' => 'debaser2_reports_graph_case_status_location'
      )
    ),
    2 => array( // reason
      'status' => array(
        'query' => 'debaser2_reports_query_case_reason_status',
        'format' => 'debaser2_reports_prepare_single_array',
        'display' => 'debaser2_reports_graph_reason_status'
      ),
      'location' => array(
        'query' => 'debaser2_reports_query_case_reason_location',
        'format' => 'debaser2_reports_prepare_single_array',
        'display' => 'debaser2_reports_graph_reason_location'
      )
    ),
    3 => array( // date
      'status' => array(
        'query' => 'debaser2_reports_query_case_date_status',
        'format' => 'debaser2_reports_prepare_single_array',
        'display' => 'debaser2_reports_graph_case_date_status'
      ),
      'location' => array(
        'query' => 'debaser2_reports_query_case_date_location',
        'format' => 'debaser2_reports_prepare_single_array',
        'display' => 'debaser2_reports_graph_case_date_location'
      )
    ),
  );

  return $query_functions[$field_type][$filter_type][$func_type];
}

/**
 *
 * Used by Tests to know which function should be called each time.
 */
function debaser2_reports_violation_functions( $field_type, $vio_flag, $func_type ){

  $query_functions = array(
      1 => array( // case_status
        'location' => array(
          'query' => 'debaser2_reports_query_violation_case_status',
          'format' => 'debaser2_reports_prepare_single_array',
          'display' => 'debaser2_reports_graph_violations_case_status'
        ),
        'nolocation' => array(
          'query' => 'debaser2_reports_query_violation_case_status',
          'format' => 'debaser2_reports_prepare_multiple_array',
          'display' => 'debaser2_reports_graph_violations_case_status'
        )
    ),

    2 => array( // month
        'location' => array(
          'query' => 'debaser2_reports_query_violation_month',
          'format' => 'debaser2_reports_prepare_single_array',
          'display' => 'debaser2_reports_graph_violations_month'
        ),
        'nolocation' => array(
          'query' => 'debaser2_reports_query_violation_month',
          'format' => 'debaser2_reports_prepare_multiple_array',
          'display' => 'debaser2_reports_graph_violations_month'
        )
    ),

    3 => array( // year
        'location' => array(
          'query' => 'debaser2_reports_query_violation_year',
          'format' => 'debaser2_reports_prepare_single_array',
          'display' => 'debaser2_reports_graph_violations_year'
        ),
        'nolocation' => array(
          'query' => 'debaser2_reports_query_violation_year',
          'format' => 'debaser2_reports_prepare_multiple_array',
          'display' => 'debaser2_reports_graph_violations_year'
        )    
    ),
    
    4 => array(
        'location' => array(
          'query' => 'debaser2_reports_query_violation_type_by_location',
          'format' => 'debaser2_reports_prepare_single_array',
          'display' => 'debaser2_reports_graph_violation_type_by_location'
        ),
        'nolocation' => array(
          'query' => 'debaser2_reports_query_violation_type_by_location',
          'format' => 'debaser2_reports_prepare_multiple_array',
          'display' => 'debaser2_reports_graph_violation_type_by_location'
        )    
    ),


  );
  return $query_functions[$field_type][$vio_flag][$func_type];
}

/**
 *
 * todo add date argument and processing here
 */
function debaser2_reports_victims_functions( $field_type, $filter_type, $func_type ){
  $query_functions = array(
      'total_violations' => array(//
        'age' => array(
          'query' => 'debaser2_reports_query_victim_total_violation_age',
          'format_date' => 'debaser2_reports_prepare_multiple_array',
          'format' => 'debaser2_reports_prepare_single_array',
          'display' => 'debaser2_reports_graph_victim_total_violation_age',
          'display_date' => 'debaser2_reports_graph_victim_total_violation_age_date',
        ),
        'ethnicity' => array(
          'query' => 'debaser2_reports_query_victim_ethnicity_victims',
          'format_date' => 'debaser2_reports_prepare_multiple_array',
          'format' => 'debaser2_reports_prepare_single_array',
          'display' => 'debaser2_reports_graph_victim_ethnicity_victims',
          'display_date' => 'debaser2_reports_graph_victim_ethnicity_victims_date',
        ),
        'political_affiliation' => array(
          'query' => 'debaser2_reports_query_victim_political_affiliation_victims',
          'format_date' => 'debaser2_reports_prepare_multiple_array',
          'format' => 'debaser2_reports_prepare_single_array',
          'display' => 'debaser2_reports_graph_victim_political_affiliation_victims',
          'display_date' => 'debaser2_reports_graph_victim_political_affiliation_victims_date',
        ),
        'gender' => array(
          'query' => 'debaser2_reports_query_victim_gender_victims',
          'format_date' => 'debaser2_reports_prepare_multiple_array',
          'format' => 'debaser2_reports_prepare_single_array',  
          'display' => 'debaser2_reports_graph_victim_gender_victims',
          'display_date' => 'debaser2_reports_graph_victim_gender_victims_date',
        ),
      ),
        
 
        'international_standards' => array(
          'age' => array(
            'query' => 'debaser2_reports_query_victim_international_standard_age',
            'format_date' => 'debaser2_reports_prepare_multiple_array',
            'format' => 'debaser2_reports_prepare_single_array',
            'display' => 'debaser2_reports_graph_victim_international_standard_age'
          ),
          'ethnicity' => array(
            'query' => 'debaser2_reports_query_victim_international_standard_ethnicity',
            'format_date' => 'debaser2_reports_prepare_multiple_array',
            'format' => 'debaser2_reports_prepare_single_array',
            'display' => 'debaser2_reports_graph_victim_international_standard_ethnicity'
          ),
          'gender' => array(
            'query' => 'debaser2_reports_query_victim_international_standard_gender',
            'format_date' => 'debaser2_reports_prepare_multiple_array',
            'format' => 'debaser2_reports_prepare_single_array',
            'display' => 'debaser2_reports_graph_victim_international_standard_gender'
          ),
          'political_affiliation' => array(
            'query' => 'debaser2_reports_query_victim_international_standard_political_affiliation',
            'format_date' => 'debaser2_reports_prepare_multiple_array',
            'format' => 'debaser2_reports_prepare_single_array',
            'display' => 'debaser2_reports_graph_victim_international_standard_political_affiliation'
          ),
        ),
        
        'others' => array(
          'gender_age' => array(
            'query' => 'debaser2_reports_query_victim_gender_by_age',
            'format' => 'debaser2_reports_prepare_multiple_array',
            'display' => 'debaser2_reports_graph_victim_gender_by_age'
          ),
          'perpetrator_age' => array(
            'query' => 'debaser2_reports_query_perpetrator_age_by_total_violations',
            'format' => 'debaser2_reports_prepare_single_array',
            'display' => 'debaser2_reports_graph_perpertrator_age_violations'
          ),
          'age_perp' => array(
            'query' => 'debaser2_reports_query_actor_age_perpetrator',
            'format' => 'debaser2_reports_prepare_single_array',
            'display' => 'debaser2_reports_graph_age_perpetrator'
          ),
        ),
        
        'political_affiliation' => array(
          'violation_type' => array(
            'query' => 'debaser2_reports_query_violation_type_by_political_affiliation',
            'format' => 'debaser2_reports_prepare_multiple_array',
            'display' => 'debaser2_reports_graph_victim_violation_type_political_affiliation'
          ),
          'ethnicity' => array(
            'query' => 'debaser2_reports_query_actor_ehnicity_political_affiliation',
            'format' => 'debaser2_reports_prepare_multiple_array',
            'display' => 'debaser2_reports_graph_victim_ethnicity_political_affiliation'
          ),
          'perpetrator_gender' => array(  
            'query' => 'debaser2_reports_query_actor_perpetrator_gender_political_affiliation',
            'format' => 'debaser2_reports_prepare_multiple_array',
            'display' => 'debaser2_reports_graph_victim_perpetrator_gender_political_affiliation'
          ),
        ),
        
        


      );

  return $query_functions[$field_type][$filter_type][$func_type];
}

