<?php

/*****************************************************************************************************************

  PREPARE DATA FOR GRAPHING

*****************************************************************************************************************/

/**
 *  returns an array containing chart data and chart labels in the format required by the graphing functions
 */
function debaser2_reports_prepare_single_array(){
  $args = func_get_args();
  foreach ($args[0] as $key => $arg){
    $$key = $arg;
  }
  $i=0;
  if($data) {
    foreach( $data as $key => $value ){
      $legend = is_array( $value ) ? key( $value ): '';
      $chart_data[0]['data'][$i] = $value[ $legend ];
      $chart_data[0]['legend'] = $legend;
      $chart_labels[] = $key;
      $i++;
    }
  } else {
    $chart_data = array();
    $chart_labels = array();
  }
  return array( 'cd' => $chart_data, 'cl' => $chart_labels );
  
}



function debaser2_reports_prepare_multiple_array(){
  $args = func_get_args();
  $i = 0;
  foreach ($args[0] as $key => $arg){
    $$key = $arg;
  }
  //get all the possible indexes
  $chart_labels = debaser2_reports_get_intermediate_array( $data );
  if($data) { 
    foreach( $data as $key => $value ){
      $chart_data[$i]['data'] = debaser2_reports_get_single_data_array( $value , $chart_labels );
      $chart_data[$i]['legend'] = $key;
      $i++;
    }
  } else {
    $chart_data = array();
    $chart_labels = array();
  }
  return array( 'cd' => $chart_data, 'cl' => $chart_labels );
  
}

function debaser2_reports_get_intermediate_array( $data ){
  $values = array();
  foreach( $data as $key => $value){
    foreach ($value as $type => $total) {
      if( !in_array( $type, $values ) )$values[] = $type;
    }
  }
  return $values ;
}

function debaser2_reports_get_single_data_array( $value, $index ){
  $ret_array = array();
  foreach ($index as $single_type) {
    $ret_array[] = array_key_exists( $single_type, $value ) ? $value[$single_type] : 0;
  }
  return $ret_array;
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
