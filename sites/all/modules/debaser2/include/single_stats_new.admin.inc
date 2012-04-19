<?php
/*****************************************************************************************************************

Created By    : Cormac McGuire - cromac
Created Date  : 29/04/11
Description   : New method for calculating single  statistics
                 
                
Updated By    : Davi Tapajos
Updated Date  : 04/05/11
Description   : Five new functions were added: "debaser2_query_case_status_violations", "debaser2_query_date_months_violation"
                and "debaser2_query_date_years_violation" to make the queries and "debaser2_query_organize" and 
                "debaser2_query_organize_get_total" to organize the data coming from each one.  

                The sixth parameter in the function "debaser2_new_correlative_bar_chart" means nothing, this number is
                calculated inside the function.
*****************************************************************************************************************/



function debaser2_select_single_query_function( $post, $func_type ){
  //matrix of graph functions - outer indexes relate to violation filter
  // inner are for actor filter
  foreach($post as $key => $variable){
    $$key = $variable;
  }
  
  // ACTOR STATS
  if( isset( $field_type ) ){
    return debaser2_get_single_actor_query_function( $field_type, $actor_type, $func_type );
  }
  //CASE STATS
  if( isset( $case_options ) ){
    // dpm($case_filters);
    return debaser2_get_single_case_query_function( $case_options, $case_location_options, $func_type );
  }
  
  //VIOLATION STATS
  if( isset( $violation_options ) ){
    return debaser2_get_single_violation_query_function( $violation_options, $violation_location_options, $func_type );
  }
  
  
}

function debaser2_get_single_actor_query_function( $field_type, $actor_type, $func_type ){
  
  $query_functions = array(
    4 => array(//Political affiliation
      0 => array(//age
        'query' => 'debaser2_query_actors_affiliation',
        'format' => 'debaser2_prepare_single_array_alt',
        'display' => 'debaser2_graph_actor_affiliation'
      ),
      2 => array(
        'query' => 'debaser2_query_actors_type_affiliation',
        'format' => 'debaser2_prepare_single_array_alt',
        'display' => 'debaser2_graph_actor_affiliation_perpetrator'
      ),
      1 => array(
        'query' => 'debaser2_query_actors_type_affiliation',
        'format' => 'debaser2_prepare_single_array_alt',
        'display' => 'debaser2_graph_actor_affiliation_victim'
      ),
      3 => array(
        'query' => 'debaser2_query_actors_type_affiliation',
        'format' => 'debaser2_prepare_single_array_alt',
        'display' => 'debaser2_graph_actor_affiliation_witness'
      ),
      
    ),
  );
  
  return $query_functions[$field_type][$actor_type][$func_type];
}

function debaser2_get_single_case_query_function( $field_type, $actor_type, $func_type ){

}

function debaser2_get_single_violation_query_function( $field_type, $actor_type, $func_type ){
  $query_functions = array(//Case Status
    1 => array(
      'query' => 'debaser2_query_case_status_violations',
      'format' => 'debaser2_prepare_multiple_array',
      'display' => 'debaser2_graph_case_status_affiliation'
    ),
    2 => array(
      'query' => 'debaser2_query_date_months_violation',
      'format' => 'debaser2_prepare_multiple_array',
      'display' => 'debaser2_graph_date_months_affiliation'
    ),
    3 => array(
      'query' => 'debaser2_query_date_years_violation',
      'format' => 'debaser2_prepare_multiple_array',
      'display' => 'debaser2_graph_date_years_affiliation'
    ),
    
    
  );

  return $query_functions[$field_type][$func_type];
}




function debaser2_new_stats_handling( $post ){
  $path = drupal_get_path( 'module', 'debaser2_reports' );
  include( $path . '/helper/debaser2_reports_func_matrix.report.inc' );
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
    
    $graph_query_func = debaser2_select_single_query_function( $post, 'query' );

    if(function_exists($graph_query_func)){
      $data = $graph_query_func( $group, $post  );
      
    }
    
    $formatted_data_func = debaser2_select_single_query_function( $post, 'format' );
    //dpm($formatted_data_func);
    if(function_exists($formatted_data_func)){
      $formatted_data = $formatted_data_func( array('data' => $data, 'standard' => $standard ) );
    }
    
    //dpm( $formatted_data );
    $graph_data_func = debaser2_select_single_query_function( $post, 'display' );
    if(function_exists($graph_data_func)){
      $chart =  $graph_data_func( $formatted_data, $group );
      return $chart;
    }
    
    
    
  }
  
  
}
/*****************************************************************************************************************

  GRAPH FUNCTIONS

*****************************************************************************************************************/

/**
 *
 */
function debaser2_graph_actor_affiliation_perpetrator(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Perpetrators';
  $chart_labels = $args[0]['cl'];
  $title = t('Perpetrators by Political Affiliation');
  $y_label = t('Perpetrators');
  $x_label = t('Actor Type');
  $key = t('Affiliation');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 150 );
}

function debaser2_graph_actor_affiliation_victim(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Victims';
  $chart_labels = $args[0]['cl'];
  $title = t('Victims by Political Affiliation');
  $y_label = t('Victims');
  $x_label = t('Affiliation');
  $key = t('Affiliation');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 150 );
}

function debaser2_graph_actor_affiliation_witness(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Witnesses';
  $chart_labels = $args[0]['cl'];
  $title = t('Witnesses by Political Affiliation');
  $y_label = t('Witnesses');
  $x_label = t('Affiliation');
  $key = t('Affiliation');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 150 );
}

function debaser2_graph_actor_affiliation(){
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $chart_data[0]['legend'] = 'Actors';
  $chart_labels = $args[0]['cl'];
  $title = t('Actors by Political Affiliation');
  $y_label = t('Actors');
  $x_label = t('Affiliation');
  $key = t('Affiliation');
  return correlative_bar_chart( $chart_data, $chart_labels, $title, $x_label, $y_label, $key, 150 );
}

function debaser2_graph_case_status_affiliation() {
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $title = t('Violations by Case Status vs Location');
  $y_label = t('Violations');
  $x_label = t('Status');
  $key = t('Status');
  return debaser2_new_correlative_bar_chart( $chart_data, $title, $x_label, $y_label, $key, 40 );
}

function debaser2_graph_date_months_affiliation() {
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $title = t('Violations by Months vs Location');
  $y_label = t('Violations');
  $x_label = t('Months');
  $key = t('Month');
  return debaser2_new_correlative_bar_chart( $chart_data, $title, $x_label, $y_label, $key, 40 );
}

function debaser2_graph_date_years_affiliation() {
  $args = func_get_args();
  $chart_data = $args[0]['cd'];
  $title = t('Violations by Years vs Location');
  $y_label = t('Violations');
  $x_label = t('Years');
  $key = t('Year');
  return debaser2_new_correlative_bar_chart( $chart_data, $title, $x_label, $y_label, $key, 40 );
}

/*****************************************************************************************************************

  QUERY FUNCTIONS

*****************************************************************************************************************/

function debaser2_query_actors_type_affiliation($group, $post){
 if($group){
   $query = 
   'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name FROM node 
   LEFT JOIN content_type_actor ON content_type_actor.vid = node.vid 
   LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
   LEFT JOIN term_data ON term_data.tid = term_node.tid 
   LEFT JOIN term_node tn2 ON tn2.vid = content_type_actor.vid 
   LEFT JOIN term_data td2 ON td2.tid = tn2.tid 
   JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
   WHERE group_nid = %d AND term_data.vid= 9 AND td2.tid = %d 
   GROUP BY term_data.name;';
   $result = db_query($query, $group, $post['actor_type']);
 }else{
   $query = 
   'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name FROM node 
   LEFT JOIN content_type_actor ON content_type_actor.vid = node.vid 
   LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
   LEFT JOIN term_data ON term_data.tid = term_node.tid 
   LEFT JOIN term_node tn2 ON tn2.vid = content_type_actor.vid 
   LEFT JOIN term_data td2 ON td2.tid = tn2.tid 
   WHERE term_data.vid= 9 AND td2.tid = %d
   GROUP BY term_data.name;';
   $result = db_query($query, $post['actor_type']);
 }
 
 while( $row = db_fetch_object( $result ) ){
   $types[] = $row; 
 }

 
 return $types;
}


function debaser2_query_actors_affiliation( $group, $post ){
  $vid = debaser2_get_vid( 'Actors' );

  $terms = taxonomy_get_tree($vid);
  if($group){
   $query = 
   'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name FROM node 
   LEFT JOIN content_type_actor ON content_type_actor.vid = node.vid 
   LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
   LEFT JOIN term_data ON term_data.tid = term_node.tid 
   LEFT JOIN term_node tn2 ON tn2.vid = content_type_actor.vid 
   LEFT JOIN term_data td2 ON td2.tid = tn2.tid 
   JOIN og_ancestry ON content_type_actor.nid = og_ancestry.nid 
   WHERE group_nid = %d AND term_data.vid= 9
   GROUP BY term_data.name;';
   
   /*foreach ($terms as $id => $value){
     $results[] = db_query($query, $group, $id);
   }*/
   $result =  db_query($query, $group);
   
 }else{
   $query = 
   'SELECT COUNT( DISTINCT content_type_actor.field_actor_name_value) AS total, term_data.name FROM node 
   LEFT JOIN content_type_actor ON content_type_actor.vid = node.vid 
   LEFT JOIN term_node ON term_node.vid = content_type_actor.vid 
   LEFT JOIN term_data ON term_data.tid = term_node.tid 
   LEFT JOIN term_node tn2 ON tn2.vid = content_type_actor.vid 
   LEFT JOIN term_data td2 ON td2.tid = tn2.tid 
   WHERE term_data.vid= 9 
   GROUP BY term_data.name;';
   /*foreach ($terms as $id => $value){
     $results[] = db_query($query, $id);
   }*/
   $result =  db_query($query);
 }
 /*$i=0;
 foreach ($results as $result) {
   while( $row = db_fetch_object( $result )){
     $rows[$i][] = $row;
   }
   $i++;
 }
 dpm( $rows );
 return $rows;*/
 while( $row = db_fetch_object( $result ) ){
   $types[] = $row; 
 }

 
 return $types;


}

/**
 * year == case status
 * name == location
 */
function debaser2_query_case_status_violations( $group, $post ){
  // dpm( $post );

  // if some location was selected, search in this location. If wasn't, search in any location using the vocabulary id.
  if ($post['violation_location_options'] > 0) {
    $field = 'tid';
    $location = $post['violation_location_options'];
  } else {
    $field = 'vid';
    $location = 3; // 3 is the vocabulary id of the location
  }

  if($group){

    $query = "SELECT COUNT(content_type_violation.vid) AS total, term_data.name AS name, field_case_nid, td_case.name AS year, 
                     (SELECT name FROM term_data td_sub JOIN term_hierarchy th_sub ON td_sub.tid = th_sub.parent WHERE th_sub.tid = td_case.tid) AS status_parent 
                FROM content_type_violation 
                JOIN node ON node.vid = content_type_violation.vid 
                JOIN content_field_case ON content_type_violation.vid = content_field_case.vid 
                JOIN content_type_case ON content_type_case.nid = field_case_nid 
                JOIN node node_case ON node_case.vid = content_type_case.vid 
                JOIN term_node ON term_node.vid = content_type_violation.vid 
                JOIN term_data ON term_data.tid = term_node.tid 
                JOIN term_node tn_case ON tn_case.vid = node_case.vid 
                JOIN term_data td_case ON td_case.tid = tn_case.tid 
                JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
               WHERE group_nid = %d 
                 AND term_data.".$field." = %d
                 AND td_case.vid = 2 
                 AND field_vio_date_value IS NOT NULL 
            GROUP BY name, year;"; 
    /* NOTE: changed (01/11/2011) content_type_violation for field_case_nid */ 
    $result =  db_query($query, $group, $location);  
 
  } else {
  
    $query = "SELECT COUNT(content_type_violation.vid) AS total, term_data.name AS name, field_case_nid, td_case.name AS year, 
                     (SELECT name FROM term_data td_sub JOIN term_hierarchy th_sub ON td_sub.tid = th_sub.parent WHERE th_sub.tid = td_case.tid) AS status_parent 
                FROM content_type_violation 
                JOIN node ON node.vid = content_type_violation.vid 
                JOIN content_field_case ON content_type_violation.vid = content_field_case.vid 
                JOIN content_type_case ON content_type_case.nid = field_case_nid 
                JOIN node node_case ON node_case.vid = content_type_case.vid 
                JOIN term_node ON term_node.vid = content_type_violation.vid 
                JOIN term_data ON term_data.tid = term_node.tid 
                JOIN term_node tn_case ON tn_case.vid = node_case.vid 
                JOIN term_data td_case ON td_case.tid = tn_case.tid 
               WHERE term_data.".$field." = %d
                 AND td_case.vid = 2 
                 AND field_vio_date_value IS NOT NULL 
            GROUP BY name, year;"; 
  

    $result =  db_query($query, $location);
  }

  $rows = array();
  while( $row = db_fetch_object( $result ) ){
    $rows[] = $row; 
  }

    foreach ($rows as $key => $value) {
      if ($rows[$key]->status_parent != NULL) {
        $rows[$key]->year = $rows[$key]->status_parent;
      }
    }

    $rows = debaser2_query_organize($rows);
  
  return $rows;

}

/**
 *
 */
function debaser2_query_date_months_violation( $group, $post ){
  if ($post['violation_location_options'] > 0) {
    $field = 'tid';
    $location = $post['violation_location_options'];
  } else {
    $field = 'vid';
    $location = 3; // 3 is the vocabulary id of the location
  }

  if($group){
    $query = "SELECT COUNT(DISTINCT content_type_violation.vid) AS total, MONTH(field_vio_date_value) AS month, YEAR(field_vio_date_value) AS year, term_data.name 
                FROM node
                JOIN content_type_violation ON content_type_violation.vid = node.vid 
                JOIN term_node ON term_node.vid = content_type_violation.vid 
                JOIN term_data ON term_data.tid = term_node.tid 
                JOIN content_field_case ON content_type_violation.vid = content_field_case.vid
                JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
               WHERE group_nid = %d 
                 AND term_data.".$field." = %d 
                 AND ( 
                   ( MONTH(field_vio_date_value) >= MONTH(CURDATE()) AND YEAR(field_vio_date_value) = (YEAR(CURDATE())-1) ) 
                   OR 
                   ( MONTH(field_vio_date_value) <= MONTH(CURDATE()) AND YEAR(field_vio_date_value) = YEAR(CURDATE()) ) 
                 ) 
            GROUP BY year, month, term_data.name
            ORDER BY year, month;";
            
    $result =  db_query($query, $group, $location);

  } else {
    $query = "SELECT COUNT(DISTINCT content_type_violation.vid) AS total, MONTH(field_vio_date_value) AS month, YEAR(field_vio_date_value) AS year, term_data.name 
                FROM node
                JOIN content_type_violation ON content_type_violation.vid = node.vid 
                JOIN term_node ON term_node.vid = content_type_violation.vid 
                JOIN term_data ON term_data.tid = term_node.tid 
               WHERE term_data.".$field." = %d 
                 AND ( 
                   ( MONTH(field_vio_date_value) >= MONTH(CURDATE()) AND YEAR(field_vio_date_value) = (YEAR(CURDATE())-1) ) 
                   OR 
                   ( MONTH(field_vio_date_value) <= MONTH(CURDATE()) AND YEAR(field_vio_date_value) = YEAR(CURDATE()) ) 
                 ) 
            GROUP BY year, month, term_data.name
            ORDER BY year, month;";
            
    $result =  db_query($query, $location);
  }

  while( $row = db_fetch_object( $result ) ){
    $rows[] = $row; 
  }
  
  if($rows) {
    foreach ($rows as $key => $value) {
      $rows[$key]->year =  date("M", mktime(0, 0, 0, $rows[$key]->month+1, 0, 0)) . ' ' . $rows[$key]->year;
    }
  }
  
  $rows = debaser2_query_organize($rows);
  return $rows;

}


function debaser2_query_date_years_violation( $group, $post ){
  if ($post['violation_location_options'] > 0) {
    $field = 'tid';
    $location = $post['violation_location_options'];
  } else {
    $field = 'vid';
    $location = 3; // 3 is the vocabulary id of the location
  }
  

  if($group){
    $query = "SELECT COUNT(content_type_violation.vid) AS total, content_type_violation.nid, YEAR(field_vio_date_value) AS year, term_data.name AS name
                FROM content_type_violation 
                JOIN node ON node.vid = content_type_violation.vid 
                JOIN term_node ON term_node.vid = content_type_violation.vid 
                JOIN term_data ON term_data.tid = term_node.tid
                JOIN content_field_case ON content_type_violation.vid = content_field_case.vid
                JOIN og_ancestry ON field_case_nid = og_ancestry.nid 
               WHERE group_nid = %d 
                 AND term_data.".$field." = %d
                 AND field_vio_date_value IS NOT NULL 
            GROUP BY year, term_data.name 
            ORDER BY year;";
         
    $result =  db_query($query, $group, $location);

  } else {
    $query = "SELECT COUNT(content_type_violation.vid) AS total, content_type_violation.nid, YEAR(field_vio_date_value) AS year, term_data.name AS name
                FROM content_type_violation 
                JOIN node ON node.vid = content_type_violation.vid 
                JOIN term_node ON term_node.vid = content_type_violation.vid 
                JOIN term_data ON term_data.tid = term_node.tid 
               WHERE term_data.".$field." = %d
                 AND field_vio_date_value IS NOT NULL 
            GROUP BY year, term_data.name 
            ORDER BY year;";
          
    $result =  db_query($query, $location);
  }

  while( $row = db_fetch_object( $result ) ){
    $rows[] = $row; 
  }
  
  
  $rows = debaser2_query_organize($rows);
  
  return $rows;
}

function debaser2_query_organize($rows){
  $names = array();
  $years = array();
  $array = array();

  if($rows) {
    foreach($rows as $key => $value) {
      $names[] = $value->name;
      $years[] = $value->year;
    }
    $names = array_unique($names);
    $years = array_unique($years);
  
    $i = 0;
    foreach($years as $year) {
      foreach($names as $name) {
        $array[$i]->year = $year;
        $array[$i]->name = $name;
        $array[$i]->total = debaser2_query_organize_get_total($rows, $name, $year);
        $i++;
      }
    }
  }
  
  // dpm($array);
  return $array;  
  
}

function debaser2_query_organize_get_total($rows, $name, $year){
  $total = 0;
  foreach($rows as $row) {
    if ($row->name == $name && $row->year == $year) {
      $total += $row->total;
    } 
  }    
  return $total;  
}


