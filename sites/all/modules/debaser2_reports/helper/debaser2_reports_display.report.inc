<?php

/**
 * display function for status vs reason for intervention
 */
function debaser2_reports_graph_actor_type() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Type'),
    'y_label' => t('Actors'),
    'x_label' => t('Type'),
    'key' => t('Type'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_actor_type_gender() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Gender vs Type'),
    'y_label' => t('Actors'),
    'x_label' => t('Gender'),
    'key' => t('Gender'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_actor_type_gender_multiple() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Gender'),
    'y_label' => t('Actors'),
    'x_label' => t('Type'),
    'key' => t('Type'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph();
}

/**
 *
 */
function debaser2_reports_graph_actor_type_ethnicity() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Ethnicity by Type'),
    'y_label' => t('Actors'),
    'x_label' => t('Ethnicity'),
    'key' => t('Ethnicity'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_actor_type_ethnicity_multiple() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Ethnicity by Type'),
    'y_label' => t('Actors'),
    'x_label' => t('Type'),
    'key' => t('Type'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_actor_type_political() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Political Affiliation'),
    'y_label' => t('Actors'),
    'x_label' => t('Political Affiliation'),
    'key' => t('Political Affiliation'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;

}

/**
 *
 */
function debaser2_reports_graph_actor_type_political_multiple() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Political Affiliation'),
    'y_label' => t('Actors'),
    'x_label' => t('Type'),
    'key' => t('Type'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;

}


/**
 *
 */
function debaser2_reports_graph_actor_type_age() {
  $args = func_get_args();
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Age'),
    'y_label' => t('Actors'),
    'x_label' => t('Age'),
    'key' => t('Age'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;

}

/**
 *
 */
function debaser2_reports_graph_actor_type_age_multiple() {
  $args = func_get_args();
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Actors by Age'),
    'y_label' => t('Actors'),
    'x_label' => t('Type'),
    'key' => t('Type'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;

}

/**
 *
 */
function debaser2_reports_graph_case_status_status(){
 $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Cases by Status'),
    'y_label' => t('Cases'),
    'x_label' => t('Status'),
    'key' => t('Status'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/*
 * display function for status vs location
 */
function debaser2_reports_graph_case_status_location() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Cases by Status(') . debaser2_reports_get_fieldname( 'debaser2_location', $args[1] ) . ')',
    'y_label' => t('Cases'),
    'x_label' => t('Status'),
    'key' => t('Status'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/*
 * display function for status vs reason for intervention
 */
function debaser2_reports_graph_reason_status() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Cases by Reason for Intervention(') . debaser2_reports_get_fieldname( 'debaser2_case_status', $args[1] ) . ')',
    'y_label' => t('Cases'),
    'x_label' => t('Reason for Intervention'),
    'key' => t('Reason for Intervention'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/*
 * display function for status vs reason for intervention
 */
function debaser2_reports_graph_reason_location() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Cases by Reason for Intervention(') . debaser2_reports_get_fieldname( 'debaser2_location', $args[1] ) . ')',
    'y_label' => t('Cases'),
    'x_label' => t('Reason for Intervention'),
    'key' => t('Reason for Intervention'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}


/*
 * display function for case date vs location
 */
function debaser2_reports_graph_case_date_status() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Cases by Date of Intervention(') . debaser2_reports_get_fieldname( 'debaser2_case_status', $args[1] ) . ')',
    'y_label' => t('Cases'),
    'x_label' => t('Date for Intervention'),
    'key' => t('Date for Intervention'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/*
 * display function for status vs reason for intervention
 */
function debaser2_reports_graph_case_date_location() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Cases by Date of Intervention(') . debaser2_reports_get_fieldname( 'debaser2_location', $args[1] ) . ')',
    'y_label' => t('Cases'),
    'x_label' => t('Date for Intervention'),
    'key' => t('Date for Intervention'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph() . $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_violations_case_status() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Violations by Case Status vs Location'),
    'y_label' => t('Violations'),
    'x_label' => t('Location'),
    'key' => t('Location'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_violations_month() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Violations by Date(months) vs Location'),
    'y_label' => t('Violations'),
    'x_label' => t('Last 12 months'),
    'key' => t('Month/Year'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_violations_year() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Violations by Date(years) vs Location'),
    'y_label' => t('Violations'),
    'x_label' => t('Years'),
    'key' => t('Year'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_violation_type_by_location() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Violations type vs Location'),
    'y_label' => t('Violations'),
    'x_label' => t('Location'),
    'key' => t('Location'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/***********************************************************************

***********************************************************************/

/**
 * Violations x Victims Display Function
 */
function debaser2_reports_graph_victim_total_violation_age() {
  $args = func_get_args();
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Age'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Victim Age'),
    'key' => t('Victim Age'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

function debaser2_reports_graph_victim_total_violation_age_date() {
  $args = func_get_args();
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Age'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Date'),
    'key' => t('Date'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_ethnicity_victims_date() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Ethnicity'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Date'),
    'key' => t('Date'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

function debaser2_reports_graph_victim_ethnicity_victims() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Ethnicity'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Victim Ethnicity'),
    'key' => t('Ethnicity'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_political_affiliation_victims_date() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Political Affiliation'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Date'),
    'key' => t('Date'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

function debaser2_reports_graph_victim_political_affiliation_victims() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Political Affiliation'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Victim Political Affiliation'),
    'key' => t('Political Affiliation'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_gender_victims() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Gender'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Victim Gender'),
    'key' => t('Gender'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

function debaser2_reports_graph_victim_gender_victims_date() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Total Violations vs Victim Gender'),
    'y_label' => t('Total Violations'),
    'x_label' => t('Date'),
    'key' => t('Date'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_international_standard_age() {
  $args = func_get_args();
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => debaser2_reports_get_fieldname( 'debaser2_violation_international_standard', $args[2] ) . t(' vs Victim Age'),
    'y_label' => t('Total Victims'),
    'x_label' => t('Victim Age'),
    'key' => t('Age'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_international_standard_ethnicity() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => debaser2_reports_get_fieldname( 'debaser2_violation_international_standard', $args[2] ) . t(' vs Victim Ethnicity'),
    'y_label' => t('Total Victims'),
    'x_label' => t('Victim Ethnicity'),
    'key' => t('Ethnicity'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_international_standard_gender() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => debaser2_reports_get_fieldname( 'debaser2_violation_international_standard', $args[2] ) . t(' vs Victim Gender'),
    'y_label' => t('Total Victims'),
    'x_label' => t('Victim Gender'),
    'key' => t('Gender'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_international_standard_political_affiliation() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => debaser2_reports_get_fieldname( 'debaser2_violation_international_standard', $args[2] ) . t(' vs Political Affiliation'),
    'y_label' => t('Total Victims'),
    'x_label' => t('Victim Political Affiliation'),
    'key' => t('Political Affiliation'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_violation_type_political_affiliation() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Violation type vs Political Affiliation'),
    'y_label' => t('Violation'),
    'x_label' => t('Victim Political Affiliation'),
    'key' => t('Political Affiliation'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_ethnicity_political_affiliation() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Ethnicity vs Political Affiliation'),
    'y_label' => t('Violation'),
    'x_label' => t('Political Affiliation'),
    'key' => t('Political Affiliation'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_perpetrator_gender_political_affiliation() {
  $args = func_get_args();
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Perpetrator gender vs Political Affiliation'),
    'y_label' => t('Violation'),
    'x_label' => t('Perpetrator age'),
    'key' => t('Political Affiliation'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_victim_gender_by_age() {
  $args = func_get_args();
  
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Gender vs Age'),
    'y_label' => t('Actor'),
    'x_label' => t('Gender'),
    'key' => t('Age'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_perpertrator_age_violations() {
  $args = func_get_args();
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Perpetrator age vs total violations'),
    'y_label' => t('Total'),
    'x_label' => t('Perpetrator'),
    'key' => t('Violation'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 *
 */
function debaser2_reports_graph_age_perpetrator() {
  $args = func_get_args();
  debaser2_reports_format_age_labels($args);
  $data = array(
    'chart_data' => $args[0]['cd'],
    'chart_labels' => $args[0]['cl'],
    'title' => t('Age vs perpetrator'),
    'y_label' => t('Total'),
    'x_label' => t('Perpetrators'),
    'key' => t('Age'),
  );
  $myData = new ChartData( $data );
  return $myData->drawGraph(). $myData->pieOutput;
}

/**
 * 
 * 
 */
function debaser2_reports_format_age_labels(&$args) {
  
  $legend = explode('_', $args[0]['cl'][0]);
  if ($legend[0] == 'age') {
    $key = 'cl';
  } else {
    $legend = explode('_', $args[0]['cd'][0]['legend']);
    if ($legend[0] == 'age') {
      $key = 'cd';
    } else {
      return false;
    }
  }
  
  foreach($args[0][$key] as $bar_key => $bar) {
    if ($key == 'cd') {
      if ($legend[0] == 'age') {    
        $legend = explode('_', $bar['legend']);
        $args[0][$key][$bar_key]['legend'] = debaser2_reports_age_formater($legend); 
      }
    } elseif ($key == 'cl') {
      if ($legend[0] == 'age') {
        $legend = explode('_', $bar);
        $args[0][$key][$bar_key] = debaser2_reports_age_formater($legend);
      }
    }
  }
  
}

/**
 * This function renames the age field from "age_x_y" to "Between x and y"
 * $key: "cd" or "cl"; "cd" is used to multiple graphs and "cl" to single graphs
 */
function debaser2_reports_age_formater($legend) {
  if ($legend[1] == '55') {
    $new_label = $legend[1] . ' or ' . $legend[2];
  } else {
    $new_label = 'Between ' . $legend[1] . ' and ' . $legend[2];
  }

  return $new_label;
}

