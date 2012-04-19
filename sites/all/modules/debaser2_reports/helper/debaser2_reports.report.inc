<?php
/*
function debaser2_reports_ (){

}
*/

/*
 * Simple function to populate select boxes in the select form
 */
function debaser2_reports_get_select ( $table_name ){
  $ret_array = array( 0 => t( '<select>' ) );
  $result = db_query( 'SELECT * FROM {%s}', $table_name );
  while( $row = db_fetch_object( $result ) ){
    $ret_array[ $row->id ] = $row->title;
  }
  return $ret_array;
}


function debaser2_reports_get_fieldname( $table_name, $id ){
  return db_result( db_query( 'SELECT title from {%s} WHERE id =%d', $table_name, $id ) );
}

function debaser2_reports_statistics_form_handling( &$form_state ){
  $post = $form_state['post'];
  $standard = ( isset( $post['int_standard'] ) ) ? $post['int_standard'] : '';
  global $user;
  $group = '';
  $path = drupal_get_path( 'module', 'debaser2_reports' );
  if( count( $post ) > 0 ){

    // include helper files
    include( $path . '/helper/debaser2_reports_func_matrix.report.inc' );
    include( $path . '/helper/debaser2_reports_formatter.report.inc' );
    include( $path . '/helper/debaser2_reports_display.report.inc' );
    include( $path . '/helper/graph_generators.php');

    // include queries files
    include( $path . '/queries/debaser2_reports_actors_queries.inc' );
    include( $path . '/queries/debaser2_reports_cases_queries.inc' );
    include( $path . '/queries/debaser2_reports_victims_queries.inc' );
    include( $path . '/queries/debaser2_reports_violations_queries.inc' );

    //get a user's group, leave null if they have more than one group
    if( count( $user->og_groups ) > 1 ) {
      $group = null;
    } else {
      foreach($user->og_groups as $key => $value){
        $group = $key;
      }
    }

    //get the query function and arguments
    $graph_query_func = debaser2_reports_select_single_query_function( $post, 'query' );
    // dpm ( $graph_query_func );
    if( function_exists( $graph_query_func['func'] ) ){
       if( isset($post['date_options']) && $post['date_options'] != '0' ){
         $data = $graph_query_func['func']( $group, $graph_query_func['arg'], $post['date_options'] );
       }else{
         $data = $graph_query_func['func']( $group, $graph_query_func['arg'] );
       }
    }
    //dpm( $data );
    
    // We need a different format when the user selected a date
    if( isset($post['date_options']) && $post['date_options'] != '0' ){
      $formatted_data_func = debaser2_reports_select_single_query_function( $post, 'format_date' );
    } else {
      $formatted_data_func = debaser2_reports_select_single_query_function( $post, 'format' );
    }
    
    // dpm($formatted_data_func['func']);
    
    if(function_exists( $formatted_data_func['func'] ) ){
      $formatted_data = $formatted_data_func['func']( array('data' => $data, 'standard' => $standard ) );
    }

    if( isset($post['date_options']) && $post['date_options'] != '0' ){
      $graph_data_func = debaser2_reports_select_single_query_function( $post, 'display_date' );
    }else{
      $graph_data_func = debaser2_reports_select_single_query_function( $post, 'display' );
    }
    //dpm ( $formatted_data );
    //dpm ( $graph_data_func );
    if(function_exists( $graph_data_func['func'] ) ){
      $chart =  $graph_data_func['func']( $formatted_data, $graph_data_func['arg'], $standard );
      return $chart;
    }



  }


}


function debaser2_reports_statistics_form( $form_values = NULL ){
	$location = debaser2_reports_get_select( 'debaser2_location' );
	$status = debaser2_reports_get_select( 'debaser2_case_status' );
	$form['#multistep'] = TRUE;
    $form['#redirect'] = FALSE;
    
	$form['field_options'] = array(
	  '#type'=>'value',
	  '#value'=>array(
	  	0=>t('<select>'), 1=>t('Actor Type'), 2=>t('Gender'), 3=>t('Ethnicity'), 4=>t('Political affiliation'), 5=>t('Age'),
	  ),
	);
	$form['actor_type'] = array(
	  '#title'=>t('Actor type'),
	  '#type'=>'select',
	  '#description'=>t('Select actor type'),
	  '#options'=>debaser2_reports_get_select( 'debaser2_actor_type' ),
	);
	$form['case_options'] = array(
	  '#title'=>t('Case Filters'),
	  '#type'=>'select',
	  '#description'=>t('Select case filter'),
	  '#options'=>array(0=>t('<select>'), 1=>t('Status'), 2=>t('Reason for Intervention'), 3=>t('Date of Intervention'), ),
	);

	$form['case_location_options'] = array(
	  '#title' => t('Case Location'),
	  '#type' => 'select',
	  '#description'=>t('Select case location'),
	  '#options' =>$location,
	);
	$form['case_status_options'] = array(
	  '#title' => t('Case Status'),
	  '#type' => 'select',
	  '#description'=>t('Select case status'),
	  '#options' =>$status,
	);

	$form['violation_options'] = array(
	  '#title'=>t('Violation Filters'),
	  '#type'=>'select',
	  '#description'=>t('Select violation filter'),
	  '#options'=>array(0=>t('<select>'), 1=>t('Case Status'), 2=>t('Date(months)'), 3=>t('Date(years)'), 4=>t('Violation type') /*4=>t('International Standard'),*/ ),
	);

	$form['violation_location_options'] = array(
	  '#title' => t('Violation Location'),
	  '#type' => 'select',
	  '#description'=>t('Select violation location'),
	  '#options' =>$location,
	);

	$form['chart_type'] = array(
	  '#title'=>t('Chart type'),
	  '#type'=>'select',
	  '#description'=>t('Select field for graph'),
	  '#options'=>array(0=>t('Bar Chart'), 1=>t('Pie Chart')),
	);
	$form['field_type'] = array(
	  '#title'=>t('Actor Filters'),
	  '#type'=>'select',
	  '#description'=>t('Select actor filter'),
	  '#options'=>$form['field_options']['#value'],
	);

	if($form_values['post']['location'])
	  $collapsed = FALSE;
	else 
	  $collapsed = TRUE;
	  
	$form['region'] = array(
	  '#title'=> t('Select Region'),
	  '#type'=>'fieldset',
	  '#collapsible'=>TRUE,
	  '#collapsed'=>$collapsed,
	);
	
	$form['region']['location'] = select_region_widget();

	$form['submit'] = array(
	  '#type'=>'submit',
	  '#value'=>t('Display Chart'),
	);

	if ($form_values!=NULL) {
		$form['results'] = array(
	      '#type' => 'item',
	      '#value' => debaser2_reports_statistics_form_handling($form_values),
	    );
	}
	return $form;

}


/*****************************************************************************************************************

  FORM HANDLING

*****************************************************************************************************************/

/**
 *
 */
function debaser2_reports_victims_violations_filter_form( $form_values = null ){
  $path = drupal_get_path('module', 'debaser2_reports');
  drupal_add_js( $path . '/js/' . 'debaser2_reports_victim_violation.js');


  //$vid = debaser2_get_vid('International Standard');
  //$standards = _debaser2_get_taxonomy_terms( $vid );

  // $result = db_query('SELECT id, title FROM {debaser2_violation_international_standard}');
  // while( $data = db_fetch_array($result) ) {
  //   $standards[$data['id']] = $data['title'];
  // }
  
  $standards = debaser2_reports_get_select('debaser2_violation_international_standard');
  $political_affiliation = debaser2_reports_get_select('debaser2_actor_political_affiliation');

  $form = array();
  $form['#multistep'] = TRUE;
  $form['#redirect'] = FALSE;

  $form['violation_victim_options'] = array(
    '#title'=>t('Violation Filters'),
	'#type'=>'select',
	'#default_value' => $form_values['post']['violation_victim_options'],
	'#description'=>t('Select violation filter'),
	'#options'=>array(
   	  0 => t('Select option'),
	  'total_violations' => t('Total Violations'),
      'international_standards' => t('International Standard') 
    ),
  );

  $form['violation_actor_options'] = array(
    '#title'=>t('Victim Options'),
	'#type'=>'select',
	'#description'=>t('Select victim filter'),
	'#options'=>array(
      '' => t( 'Select Victim Filter' ),
	  'age' =>t('Victim Age'),
	  'ethnicity' =>t('Victim Ethnicity'),
	  'gender' =>t('Victim Gender'),
	  'political_affiliation' =>t('Victim Political Affiliation')
	),
	'#default_value' => 1
  );

  $form['int_standard'] = array(
    '#title' => t('International Standard'),
    '#type' => 'select',
    '#description' => t('Select International Standard'),
    '#disabled' => false,
    '#default_value' => $form_values['post']['int_standard'],
    '#options' => $standards,
  );

  $form['date_options'] = array(
	'#title'=>t('Date Options'),
	'#type'=>'select',
	'#description'=>t('Select date filter'),
	'#options'=>array(
      0 => t( 'Select Date Filter' ),
	  'month' => t('Months'),
	  'year' => t('Years'),
	),
	'#default_value' => 0
  );
  
  
  $form['political_affiliation_options'] = array(
    '#title' => t('Victims'),
	'#type' => 'select',
	'#default_value' => $form_values['post']['political_affiliation_options'],
	'#description' => t('Political affiliation options'),
	'#options' => array(
 	  0 => t('Select option'),
	  'violation_type' => t('Violation type'), // victim
      'perpetrator_gender' => t('Perpetrator gender'), // actor
      'ethnicity' => t('Ethnicity'), // actor
    ),
  );

  $form['political_affiliation'] = array(
    '#title' => t('Political affiliation'),
	'#type' => 'select',
	'#default_value' => $form_values['post']['political_affiliation'],
	'#description' => t('Political affiliation filter'),
	'#options' => $political_affiliation
  );
  
  $form['other_statistics'] = array(
    '#title' => t('Other statistics'),
	'#type' => 'select',
	'#default_value' => $form_values['post']['other_statistics'],
	'#description' => t(''),
	'#options' => array(
 	  0 => t('Select option'),
	  'gender_age' => t('Gender x Victims age'), // victim
      'perpetrator_age' => t('Perpetrator age x Violations'), // actor
      'age_perp' => t('Age x Perpetrators'), // actor
    ),
  );

  $form['submit'] = array(
    '#type'=>'submit',
	'#value'=>t('Display Chart')
  );

  if ($form_values!=NULL) {
    $form['results'] = array(
	  '#type' => 'item',
	  '#value' => debaser2_reports_statistics_form_handling($form_values),
	);
  }

  return $form;


}

/**
 *
 *
 */
function debaser2_reports_execute_query($sql = NULL, $group = NULL, $param = NULL) {

  if($sql) {

    if ($group) {
      if($param) {
        $results = db_query($sql, $group, $param);
      } else {
        $results = db_query($sql, $group);
      }
    } else {
      if($param) {
        $results = db_query($sql, $param);
      } else {
        $results = db_query($sql);
      }
    }

  } else {
    $results = NULL;
  }

  return $results;
}

