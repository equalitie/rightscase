<?php
/*****************************************************************************************************************

Created By    : Cormac McGuire - cromac
Created Date  : 21/4/2011
Description   : get the stats to build correlations between actors and violations
                Displays a form showing the user the options they can select from when building their graphs
                Functions that process this graph are then selected in debaser2_actors_violations_handling which
                examines an array defined in debaser2_select_query_function to find the approprriate function
                 
                
Updated By    :
Updated Date  :
Description   :
*****************************************************************************************************************/



/*****************************************************************************************************************

  PAGE CALLBACKS

*****************************************************************************************************************/
/*
page callback for stats/correlative_statistics defined in debaser.module hook_menu implementation

displays the form and the graph
*/
function debaser2_correlative_page(){
  return drupal_get_form('debaser2_correlative_form');
}

/*****************************************************************************************************************

  FORM HANDLING

*****************************************************************************************************************/

/**
 *
 */
function debaser2_correlative_form( $form_values = null ){
  $vid = debaser2_get_vid('International Standard');
  $standards = _debaser2_get_taxonomy_terms( $vid );
  $form = array();
  $form['#multistep'] = TRUE;
  $form['#redirect'] = FALSE;
  
  $form['violation_options'] = array(
		'#title'=>t('Violation Filters'),
		'#type'=>'select',
		'#default_value' => $form_values['post']['violation_options'],
		'#description'=>t('Select violation filter'),
		'#options'=>array(0=>t('Total Violations'), 1=>t('Date (Years)'), 2=>t('International Standard') ),
	);
  
  $form['actor_options'] = array(
		'#title'=>t('Victim Options'),
		'#type'=>'select',
		'#description'=>t('Select victim filter'),
		
		'#options'=>array(
		  0 => t( 'Select Victim Filter' ), 
		  1=>t('Victim Age'), 
		  2=>t('Victim Ethnicity'),
		  3=>t('Victim Gender'), 
		  4=>t('Victim Political Affiliation') 
		),
		'#default_value' => 1
	);
	
	
	$form['int_standard'] = array(
	  '#title' => t('International Standard'),
	  '#type' => 'select',
	  '#description' => t('Select International Standard'),
	  '#disabled' => false,
	  '#options' => $standards,
	);
	
	$form['submit'] = array(
		'#type'=>'submit',
		'#value'=>t('Display Chart')
  );
  
  
  if ($form_values!=NULL) {
		$form['results'] = array(
	      '#type' => 'item',
	      '#value' => debaser2_actors_violations_handling($form_values['post']),
	    );
	}
	
	return $form;
  
  
}


/*****************************************************************************************************************

  FUNCTION MATRICES
  The following function decides which functions are to be used to retrieve, format and display the data for the 
  graphs

*****************************************************************************************************************/

/**
 *
 */
function debaser2_select_query_function( $actor_filter, $violation_filter, $func_type ){
  //matrix of graph functions - outer indexes relate to violation filter
  // inner are for actor filter

  $query_functions = array(
    
    0 => array(//no violation option selected
      1 => array(//age
        'query' => 'debaser2_actors_violations_age',
        'format' => 'debaser2_prepare_single_array',
        'display' => 'debaser2_graph_actor_age_violation'
      ),
      2 => array(//ethnicity
        'query' => 'debaser2_actors_violations_ethnicity',
        'format' => 'debaser2_prepare_single_array_alt',
        'display' => 'debaser2_graph_actor_violation_ethnicity'
      ),
      3 => array(//gender
        'query' => 'debaser2_actors_violations_gender',
        'format' => 'debaser2_prepare_single_array',
        'display' => 'debaser2_graph_actor_gender_violation',
      ),
      4 => array(//political affiliation
        'query' => 'debaser2_actors_violations_affiliation',
        'format' => 'debaser2_prepare_single_array_alt',
        'display' => 'debaser2_graph_actor_violation_affiliation',
      ),
      
    ),
    
    1 => array(//Date
      2 => array(//ethnicity
        'query' => 'debaser2_actors_violations_date_ethnicity',
        'format' => 'debaser2_prepare_multiple_array',
        'display' => 'debaser2_graph_actor_violation_date_ethnicity',
      ),
      3 => array(//gender
        'query' => 'debaser2_actors_violations_date_gender',
        'format' => 'debaser2_prepare_multiple_array_alt',
        'display' => 'debaser2_graph_actor_violation_date_gender',
      ),
      4 => array(//Political Affiliation
        'query' => 'debaser2_actors_violations_date_affiliation',
        'format' => 'debaser2_prepare_multiple_array',
        'display' => 'debaser2_graph_actor_violation_date_affiliation',
      ),
      
    ),
    2 => array(//International standard selected
      2 => array(//ethnicity
        'query' => 'debaser2_actors_violations_standard_ethnicity',
        'format' => 'debaser2_prepare_single_array_alt',
        'display' => 'debaser2_graph_actor_violation_standard_ethnicity',
      ),
      3 => array(//gender
        'query' => 'debaser2_actors_violations_standard_gender',
        'format' => 'debaser2_prepare_single_array',
        'display' => 'debaser2_graph_actor_violation_standard_gender',
      ),
      
      
    ),
  );
  
  return $query_functions[$violation_filter][$actor_filter][$func_type];
}

/*
This function calls the functions defined in debaser2_select_query_function
*/

function debaser2_actors_violations_handling( $post ){
  $standard = $post['int_standard'];
  $group = '';
  if( count( $post ) > 0 ){
    $path = drupal_get_path( 'module', 'debaser2' );
    include( $path . '/include/graph_generators.php');
    global $user;
    if( count( $user->og_groups ) > 1 )$group = null;
    else {
      
      foreach($user->og_groups as $key => $value){
        $group = $key;
      }
    
    }
    
    $graph_query_func = debaser2_select_query_function( $post['actor_options'], $post['violation_options'], 'query' );


    if(function_exists($graph_query_func)){
      $data = $graph_query_func( $group, $standard );
    }
    
    $formatted_data_func = debaser2_select_query_function( $post['actor_options'], $post['violation_options'], 'format' );
    if(function_exists($formatted_data_func)){
      $formatted_data = $formatted_data_func( array('data' => $data, 'standard' => $standard ) );
    }
    
    $graph_data_func = debaser2_select_query_function( $post['actor_options'], $post['violation_options'], 'display' );
    if(function_exists($graph_data_func)){
      $chart =  $graph_data_func( $formatted_data, $group, $standard );
      return $chart;
    }
    
    
    
  }
  
  
}



/*****************************************************************************************************************

  PREPARE DATA FOR GRAPHING

*****************************************************************************************************************/

/**
 *  returns an array containing chart data and chart labels in the format required by the graphing functions
 */
function debaser2_prepare_single_array(){

  $args = func_get_args();
  foreach ($args[0] as $key => $arg){
    $$key = $arg;
  }
  
  $i=0;
  if($data) {
    foreach( $data as $key => $value ){
      $chart_data[0]['data'][$i] = $value;
      $chart_labels[] = $key;
      $i++;
    }
  } else {
    $chart_data = array();
    $chart_labels = array();
  }
  return array( 'cd' => $chart_data, 'cl' => $chart_labels );
  
}


function debaser2_prepare_single_array_alt(){

  $args = func_get_args();
  foreach ($args[0] as $key => $arg){
    $$key = $arg;
  }
 
  if($data) {
    foreach( $data as $item ){
      $chart_data[0]['data'][$i] = $item->total;
      $chart_labels[] = $item->name;
      $i++;
    }
  } else {
    $chart_data = array();
    $chart_labels = array();
  }
  return array( 'cd' => $chart_data, 'cl' => $chart_labels );
}


function debaser2_prepare_multiple_array(){
  $args = func_get_args();
  foreach ($args[0] as $key => $arg){
    $$key = $arg;
  }

  if($data) { 
    foreach( $data as $key => $value ){
      $chart_data[$value->year][$value->name] = $value->total;
    }
  } else {
    $chart_data = array();
    $chart_labels = array();
  }

  return array( 'cd' => $chart_data, 'cl' => $chart_labels );
  
}

function debaser2_prepare_multiple_array_alt(){
  $args = func_get_args();
  foreach ($args[0] as $key => $arg){
    $$key = $arg;
  }

  if($data) {
    foreach( $data as $key => $value ){
      foreach($value as $entry){
        $chart_data[$entry->year][$key] = $entry->total;
      }
    }
  } else {
    $chart_data = array();
    $chart_labels = array();
  }
  return array( 'cd' => $chart_data, 'cl' => $chart_labels );
  
}


/*****************************************************************************************************************

  SEND DATA TO OPEN FLASH CHART

*****************************************************************************************************************/

/*

correlative_bar_chart($chart_data, $chart_labels, $title, $x_label, $y_label, $key
*/
function debaser2_graph_actor_age_violation(){
  $args = func_get_args();

  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Age';
  $chart_labels = $args[0]['cl'];
  $title = t('Violation Victims by Age');
  $y_label = t('Victims');
  $x_label = t('Age Groups');
  $key = t('Age');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 15 );
  
}


function debaser2_graph_actor_gender_violation(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Gender';
  $chart_labels = $args[0]['cl'];
  $title = t('Violation Victims by Gender');
  $y_label = t('Victims');
  $x_label = t('Gender');
  $key = t('Gender');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 15 );
}


function debaser2_graph_actor_violation_ethnicity(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Ethnicity';
  $chart_labels = $args[0]['cl'];
  $title = t('Violation Victims by Ethnicity');
  $y_label = t('Victims');
  $x_label = t('Ethnicity');
  $key = t('Ethnicity');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 15 );
}

function debaser2_graph_actor_violation_affiliation(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Affiliation';
  $chart_labels = $args[0]['cl'];
  $title = t('Violation Victims by Affiliation');
  $y_label = t('Victims');
  $x_label = t('Affiliation');
  $key = t('Affiliation');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 15 );
}

function debaser2_graph_actor_violation_standard_ethnicity(){
  $args = func_get_args();
  $standard = 	taxonomy_get_term( $args[2] );
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = t('International Standard ') . '(' . $standard->name . ')';
  $chart_labels = $args[0]['cl'];
  $title = t('International Standard ') . '(' . $standard->name . ')';
  $y_label = t('Victims');
  $x_label = $standard->name;
  $key =  $standard->name;
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 15 );
}


function debaser2_graph_actor_violation_standard_gender(){
  $args = func_get_args();
  $standard = 	taxonomy_get_term( $args[2] );
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Gender';
  $chart_labels = $args[0]['cl'];
  $title = t('Violation Victims by International Standard') .' ( ' . $standard->name . ' ) '. t('vs Gender');
  $y_label = t('Victims');
  $x_label = t('Gender');
  $key = t('Gender');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 15 );
}

function debaser2_graph_actor_violation_date_ethnicity(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $title = t('Violation Victims by Date vs Ethnicity');
  $y_label = t('Victims');
  $x_label = t('Year');
  $key = t('Year');
  return debaser2_new_correlative_bar_chart( $chart_data, $title, $x_label, $y_label, $key, 15 );
}

function debaser2_graph_actor_violation_date_gender(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $title = t('Violation Victims by Date vs Gender');
  $y_label = t('Victims');
  $x_label = t('Year');
  $key = t('Year');
  return debaser2_new_correlative_bar_chart( $chart_data, $title, $x_label, $y_label, $key, 15 );
}

function debaser2_graph_actor_violation_date_affiliation(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $title = t('Violation Victims by Date vs Political Affiliation');
  $y_label = t('Victims');
  $x_label = t('Years');
  $key = t('Gender');
  return debaser2_new_correlative_bar_chart( $chart_data, $title, $x_label, $y_label, $key, 15 );
}




/*****************************************************************************************************************

  QUERIES`

*****************************************************************************************************************/
/**
 * get the total of men and women assigned as victims of violations
 */
function debaser2_actors_violations_gender($group = null){
  
  if( !$group ){ 
    $query = 
      'SELECT
      (
        SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value)  
        FROM node  
        LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
        LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim. field_violation_victim_nid 
        WHERE field_gender_value = \'male\'
      ) AS men, (
        SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value)  
        FROM node  
        LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
        LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim. field_violation_victim_nid 
        WHERE field_gender_value = \'female\'
      ) as women ;';
    $result = db_query( $query );
  } else {
    $query = 
      'SELECT
      (
           SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value)  
             FROM node  
        LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
        LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim. field_violation_victim_nid 
             JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
             JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
            WHERE field_gender_value = \'male\' 
              AND group_nid = %d
      ) AS men, (
           SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value)  
             FROM node  
        LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
        LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim. field_violation_victim_nid
             JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
             JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
            WHERE field_gender_value = \'female\' 
              AND group_nid = %d
      ) as women ;';
    $result = db_query( $query, $group, $group );
  }
  
  $total_men_women = db_fetch_object( $result );
 
  return $total_men_women;
}

function debaser2_actors_violations_age( $group = null ){
  global $user;
  if( !$group ){ 
    $query = 
    'SELECT (
         SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) 
           FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
          WHERE field_age_value >= 0 
            AND field_age_value <= 18
    ) AS "0-18", (
         SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) 
           FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
          WHERE field_age_value > 18 
            AND field_age_value <= 35
    ) AS "19-35", (
         SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) 
           FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
          WHERE field_age_value > 35 
            AND field_age_value < 55
    ) AS "36-54", (
         SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) 
           FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
          WHERE field_age_value > 55 
    ) AS "55+";';
    $result = db_query( $query ); 
  } else {
    $query = 
    'SELECT(
         SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) 
           FROM node
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
           JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
           JOIN og_ancestry ON field_case_nid = og_ancestry.nid  
          WHERE group_nid = %d 
            AND field_age_value >= 0 
            AND field_age_value <= 18
     ) as \'0-18\', (
         SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) 
           FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
           JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
           JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
          WHERE group_nid = %d 
            AND field_age_value > 18 
            AND field_age_value <= 36
     ) AS \'19-36\', (
         SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) 
           FROM node LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
           JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
           JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
          WHERE group_nid = %d 
            AND field_age_value > 36 
            AND field_age_value <= 54
     ) AS \'36-54\', (
         SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) 
           FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid  
      LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
           JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
           JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
          WHERE group_nid = %d 
            AND field_age_value > 54 
     ) AS \'55+\';';
    $result = db_query( $query, $group, $group, $group, $group );
  }
  
  $ages = db_fetch_object( $result );
  return $ages;
}

function debaser2_actors_violations_ethnicity( $group = null ){
  $e_vid = debaser2_get_vid( 'Ethnicity' );
  if( !$group ){
    $query = '
       SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name 
         FROM node LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid 
        WHERE term_data.vid = %d 
     GROUP BY term_data.name;'; 
    $result = db_query( $query, $e_vid );
  } else {
    $query = 
    '  SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid
         JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
         JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
        WHERE group_nid = %d 
          AND term_data.vid = %d 
     GROUP BY term_data.name;';
    $result = db_query( $query, $group, $e_vid );
  }
  
  while( $ethnicity = db_fetch_object( $result ) ){
    $ethnicities[]  = $ethnicity;
  }
  
  return $ethnicities;
}

function debaser2_actors_violations_affiliation( $group = null ){
  $e_vid = debaser2_get_vid( 'Political Affiliation' );
  if( !$group ){
    $query = 
      'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid 
        WHERE term_data.vid = %d 
     GROUP BY term_data.name;
    '; 
    $result = db_query( $query, $e_vid );
  } else {
    $query = 
      'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid
         JOIN content_field_case ON content_field_case.vid = content_field_violation_victim.vid
         JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
        WHERE group_nid = %d 
          AND term_data.vid = %d 
     GROUP BY term_data.name;';
    $result = db_query( $query, $group, $e_vid );
  }
  
  while( $affiliation = db_fetch_object( $result ) ){
    $affiliations[]  = $affiliation;
  }

  return $affiliations;
}



function debaser2_actors_violations_standard_ethnicity( $group = null, $standard = null ){
  $e_vid = debaser2_get_vid( 'Ethnicity' );
  if( !$group ){
    $query = 
      'SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) as total, td2.name AS name FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_field_violation_victim.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid 
    LEFT JOIN term_node tn2 ON tn2.vid = content_type_actor.vid 
    LEFT JOIN term_data td2 ON td2.tid = tn2.tid 
        WHERE term_data.tid = %d 
          AND td2.vid = %d 
     GROUP BY name;';

    $result = db_query( $query, $standard, $e_vid );
  } else {
    $query = 
      'SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) as total, td2.name AS name FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_field_violation_victim.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid 
    LEFT JOIN term_node tn2 ON tn2.vid = content_type_actor.vid 
    LEFT JOIN term_data td2 ON td2.tid = tn2.tid JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
        WHERE group_nid = %d 
          AND term_data.tid = %d 
          AND td2.vid = %d 
     GROUP BY name;';
    $result = db_query( $query, $group, $standard, $e_vid );
  }
  
  while( $ethnicity = db_fetch_object( $result ) ){
    
    $ethnicities[]  = $ethnicity;
  }
  
  return $ethnicities;
}


function debaser2_actors_violations_standard_gender( $group = null, $standard = null ){
  $s_vid = debaser2_get_vid( 'International Standard' );
  if( !$group ){
    $query = 
      'SELECT(
           SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) FROM node 
        LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
        LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
        LEFT JOIN term_node ON term_node.vid = content_field_violation_victim.vid 
        LEFT JOIN term_data ON term_data.tid = term_node.tid 
            WHERE term_data.vid = %d 
              AND term_data.tid = %d 
              AND field_gender_value = \'male\' 
      ) AS men, (
           SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) FROM node 
        LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
        LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
        LEFT JOIN term_node ON term_node.vid = content_field_violation_victim.vid 
        LEFT JOIN term_data ON term_data.tid = term_node.tid 
            WHERE term_data.vid = %d
              AND term_data.tid = %d
              AND field_gender_value = \'female\' 
      ) as women;';
    $result = db_query( $query, $s_vid, $standard, $s_vid, $standard );
  } else {
    $query = 
    'SELECT(
         SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value), term_data.name FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
      LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
      LEFT JOIN term_node ON term_node.vid = content_field_violation_victim.vid 
      LEFT JOIN term_data ON term_data.tid = term_node.tid 
           JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
          WHERE group_nid = %d 
            AND term_data.vid = %d
            AND term_data.tid = %d
            AND field_gender_value = \'male\'
       GROUP BY term_data.name
    ) AS men, (
         SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value), term_data.name FROM node 
      LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
      LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
      LEFT JOIN term_node ON term_node.vid = content_field_violation_victim.vid 
      LEFT JOIN term_data ON term_data.tid = term_node.tid 
           JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
          WHERE group_nid = %d 
            AND term_data.vid = %d 
            AND term_data.tid = %d 
            AND field_gender_value = \'female\' 
       GROUP BY term_data.name
    ) as women;';
    $result = db_query( $query, $group, $s_vid, $standard, $s_vid, $standard );
  }
  
  $total_men_women = db_fetch_object( $result );
  
  return $total_men_women;
}



function debaser2_actors_violations_date_gender( $group = null ){
  if( !$group ){
    $m_query = 
      'SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value)as total, YEAR(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid 
        WHERE YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value) <= 2011 
          AND field_gender_value = \'male\' 
     GROUP BY year;';
    $f_query = 
      'SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) as total, YEAR(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid 
        WHERE YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value) <= 2011 
          AND field_gender_value = \'female\' 
     GROUP BY year;';
    
    $m_result = db_query( $m_query );
    $f_result = db_query( $f_query );
    
  } else {
    $m_query = 
      'SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) as total, YEAR(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid 
         JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
        WHERE group_nid = %d 
          AND YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value) <= 2011 
          AND field_gender_value = \'male\' 
     GROUP BY year;';
    
    $f_query = 
      'SELECT COUNT(DISTINCT content_type_actor.field_actor_name_value) as total, YEAR(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid= content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid 
         JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
        WHERE group_nid = %d 
          AND YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value) <= 2011 
          AND field_gender_value = \'female\' 
     GROUP BY year;';
    $m_result = db_query( $m_query, $group );
    $f_result = db_query( $f_query, $group );
  }
  
  while( $female_row = db_fetch_object( $f_result ) ){
    $females[]  = $female_row;
  }
  while( $male_row = db_fetch_object( $m_result ) ){
    $males[]  = $male_row;
  }

  $data = array( 'male' => $males, 'female' => $females );

  return $data;
}

function debaser2_actors_violations_date_ethnicity( $group = null ){
  $e_vid = debaser2_get_vid( 'Ethnicity' );
  if( !$group ){
    $query = 
      'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name, year(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid LEFT JOIN term_data ON term_data.tid = term_node.tid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid 
        WHERE YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value) <= 2011 
          AND term_data.vid = %d 
     GROUP BY year, term_data.name; '; 

    $result = db_query( $query, $e_vid );
  } else {
    $query = 
      'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name, year(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid 
         JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
        WHERE group_nid = %d 
          AND YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value) <= 2011 
          AND term_data.vid = %d 
     GROUP BY year, term_data.name; ';
    $result = db_query( $query, $group, $e_vid );
  }
  
  while( $ethnicity = db_fetch_object( $result ) ){

    $ethnicities[]  = $ethnicity;
  }
  
  return $ethnicities;
}

function debaser2_actors_violations_date_affiliation( $group = null ){
  $pa_vid = debaser2_get_vid( 'Political Affiliation' );
  if( !$group ){
    $query = 
      'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name, year(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid 
        WHERE YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value)<= 2011 
          AND term_data.vid=%d 
     GROUP BY year, term_data.name;';
    
    $result = db_query( $query, $pa_vid );
  } else {
    $query = 
      'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name, year(field_vio_date_value) AS year FROM node 
    LEFT JOIN content_field_violation_victim ON content_field_violation_victim.vid = node.vid 
    LEFT JOIN content_type_actor ON content_type_actor.nid = content_field_violation_victim.field_violation_victim_nid 
    LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
    LEFT JOIN term_data ON term_data.tid = term_node.tid 
    LEFT JOIN content_type_violation ON content_type_violation.nid = content_field_violation_victim.nid
         JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
        WHERE group_nid = %d 
          AND YEAR(field_vio_date_value) >= 1970 
          AND YEAR(field_vio_date_value)<= 2011 
          AND term_data.vid= %d 
     GROUP BY year, term_data.name;';
    $result = db_query( $query, $group, $pa_vid );
  }
  
  
  while( $ethnicity = db_fetch_object( $result ) ){
    $ethnicities[]  = $ethnicity;
  }
  
  return $ethnicities;
}

function debaser2_actors_violations_( $group = null ){
  $e_vid = debaser2_get_vid( 'Ethnicity' );
  if( !$group ){
    $query = ''; 
    $result = db_query( $query, $e_vid );
  } else {
    $query = 
    '';
    $result = db_query( $query, $group, $e_vid );
  }
  
  while( $ethnicity = db_fetch_object( $result ) ){
    $ethnicities[]  = $ethnicity;
  }
  
  return $ethnicities;
}






