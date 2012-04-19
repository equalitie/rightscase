<?php


/**********************************

         ACTOR QUERIES

/*********************************/

/**
 *
 *
 */
function debaser2_reports_query_actor_type($group = NULL, $type = NULL) {
  $results = array();
  $result = debaser2_reports_query_actor_type_sql($group, $type);
  while ($row = db_fetch_object($result)) {
    $results[$row->type] = $row->count;
  }
  
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_actor_type_sql($group = NULL, $type = NULL) {
  $sql = "SELECT COUNT( {debaser2_actor}.id ) AS count, {debaser2_actor_type}.title AS type
            FROM {debaser2_actor}
            JOIN {debaser2_actor_type}
              ON {debaser2_actor}.debaser2_actor_type_id = {debaser2_actor_type}.id
           WHERE 1 = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_actor}.group_id = %d ";
  }

  if ($type) {
    $sql .= " AND {debaser2_actor}.debaser2_actor_type_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_actor_type}.title ";

  return debaser2_reports_execute_query($sql, $group, $type);
}

/**
 *
 *
 */
function debaser2_reports_query_actor_gender($group = NULL, $status = NULL) {
  $results = array();
  $result = debaser2_reports_query_actor_gender_sql($group, $status);
  while ($row = db_fetch_object($result)) {
    $results[$row->gender][$row->type] = $row->count;
  }
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_actor_gender_sql($group = NULL, $type = NULL) {
  $sql = "SELECT COUNT( {debaser2_actor}.id ) AS count, {debaser2_actor_type}.title AS type, {debaser2_actor_gender}.title AS gender
            FROM {debaser2_actor}
            JOIN {debaser2_actor_type}
              ON {debaser2_actor}.debaser2_actor_type_id = {debaser2_actor_type}.id
            JOIN {debaser2_actor_gender}
              ON {debaser2_actor}.debaser2_actor_gender_id = {debaser2_actor_gender}.id
           WHERE 1 = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_actor}.group_id = %d ";
  }

  if ($type) {
    $sql .= " AND {debaser2_actor}.debaser2_actor_type_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_actor_gender}.title, {debaser2_actor_type}.title ";
  return debaser2_reports_execute_query($sql, $group, $type);
}

function debaser2_reports_query_actor_ethnicity($group = NULL, $status = NULL) {
  $results = array();
  $result = debaser2_reports_query_actor_ethnicity_sql($group, $status);
  while ($row = db_fetch_object($result)) {
    $results[$row->ethnicity][$row->type] = $row->count;
  }
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_actor_ethnicity_sql($group = NULL, $type = NULL) {
  $sql = "SELECT COUNT( {debaser2_actor}.id ) AS count, {debaser2_actor_type}.title AS type, {debaser2_actor_ethnicity}.title AS ethnicity
            FROM {debaser2_actor}
            JOIN {debaser2_actor_type}
              ON {debaser2_actor}.debaser2_actor_type_id = {debaser2_actor_type}.id
            JOIN {debaser2_actor_ethnicity}
              ON {debaser2_actor}.debaser2_actor_ethnicity_id = {debaser2_actor_ethnicity}.id
           WHERE 1 = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_actor}.group_id = %d ";
  }

  if ($type) {
    $sql .= " AND {debaser2_actor}.debaser2_actor_type_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_actor_ethnicity}.title, {debaser2_actor_type}.title ";

  return debaser2_reports_execute_query($sql, $group, $type);
}

function debaser2_reports_query_actor_political_affiliation($group = NULL, $status = NULL) {
  $results = array();
  $result = debaser2_reports_query_actor_political_affiliation_sql($group, $status);
  while ($row = db_fetch_object($result)) {
    $results[$row->political_affiliation][$row->type] = $row->count;
  }
  return $results;
}
/**
 *
 *
 */
function debaser2_reports_query_actor_political_affiliation_sql($group = NULL, $type = NULL) {
  $sql = "SELECT COUNT( {debaser2_actor}.id ) AS count, {debaser2_actor_type}.title AS type, {debaser2_actor_political_affiliation}.title AS political_affiliation
            FROM {debaser2_actor}
            JOIN {debaser2_actor_type}
              ON {debaser2_actor}.debaser2_actor_type_id = {debaser2_actor_type}.id
            JOIN {debaser2_actor_political_affiliation}
              ON {debaser2_actor}.debaser2_actor_political_affiliation_id = {debaser2_actor_political_affiliation}.id
           WHERE 1 = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_actor}.group_id = %d ";
  }

  if ($type) {
    $sql .= " AND {debaser2_actor}.debaser2_actor_type_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_actor_political_affiliation}.title, {debaser2_actor_type}.title ";

  return debaser2_reports_execute_query($sql, $group, $type);
}

/**
 *
 *
 */
function debaser2_reports_query_actor_age($group = NULL, $type = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();
  foreach($fields as $field) {
    $result = debaser2_reports_query_actor_age_sql($field, $group, $type);
    while ($row = db_fetch_object($result)) {
      $results[$field][$row->type] = $row->age_range;
    }
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_actor_age_sql($field, $group, $type){
  $sql = "SELECT COUNT(".$field.") AS age_range, {debaser2_actor_type}.title AS type
            FROM {debaser2_actor}
            JOIN {debaser2_actor_type}
              ON {debaser2_actor}.debaser2_actor_type_id = {debaser2_actor_type}.id
           WHERE ".$field." = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_actor}.group_id = %d ";
  }

  if ($type) {
    $sql .= " AND {debaser2_actor}.debaser2_actor_type_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_actor_type}.title ";

  return debaser2_reports_execute_query($sql, $group, $type);
}


/**
 * Luis Fernando
 *
 */
function debaser2_reports_query_actor_perpetrator_gender_political_affiliation( $group = NULL, $param = NULL ) {
  $results = array();
  $result = debaser2_reports_query_actor_perpetrator_gender_political_affiliation_sql( $group, $param );
  while ($row = db_fetch_object($result)) {
    $results[$row->gender][$row->political_affiliation] = $row->count;
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_actor_perpetrator_gender_political_affiliation_sql( $group, $param ) {
  $sql = "SELECT count(a.id) AS count, g.title as gender, p.title as political_affiliation
            FROM {debaser2_actor} a
      INNER JOIN {debaser2_actor_gender} g 
              ON (g.id = a.debaser2_actor_gender_id )
      INNER JOIN {debaser2_actor_political_affiliation} p 
              ON (p.id = a.debaser2_actor_political_affiliation_id )
           WHERE a.debaser2_actor_type_id = 2 ";

  if ($group) {
    $sql .= " AND a.group_id = %d ";
  }
  
  if ($param) {
    $sql .= " AND a.debaser2_actor_political_affiliation_id = %d ";
  }
  

  $sql .= " GROUP BY g.title, p.title ";

  return debaser2_reports_execute_query($sql, $group, $param);
}

/**
 *
 *
 */
function debaser2_reports_query_actor_ehnicity_political_affiliation( $group = NULL, $param = NULL ) {
  $results = array();
  $result = debaser2_reports_query_actor_ehnicity_political_affiliation_sql( $group, $param );
  while ($row = db_fetch_object($result)) {
    $results[$row->ethnicity][$row->political_affiliation] = $row->count;
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_actor_ehnicity_political_affiliation_sql( $group, $param ) {
  $sql = "SELECT count(a.id) AS count, e.title as ethnicity, p.title as political_affiliation
            FROM {debaser2_actor} a
      INNER JOIN {debaser2_actor_ethnicity} e 
              ON (e.id = a.debaser2_actor_ethnicity_id )
      INNER JOIN {debaser2_actor_political_affiliation} p 
              ON (p.id = a.debaser2_actor_political_affiliation_id )
           WHERE 1 = 1 ";

  if ($group) {
    $sql .= " AND a.group_id = %d ";
  }

  if ($param) {
    $sql .= " AND a.debaser2_actor_political_affiliation_id = %d ";
  }
  
  $sql .= " GROUP BY e.title, p.title ";

  return debaser2_reports_execute_query($sql, $group, $param);
}

/**
 *
 *
 */
function debaser2_reports_query_actor_age_perpetrator( $group = NULL, $param = NULL ) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();
  $result = debaser2_reports_query_actor_age_perpetrator_sql($group, $param);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      $results[$field] = $row->$field;
    }
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_actor_age_perpetrator_sql( $group, $param ) {
  $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more
            FROM {debaser2_actor} a
           WHERE a.debaser2_actor_type_id = 2  ";

  if ($group) {
    $sql .= " AND a.group_id = %d ";
  }

  $sql .= " GROUP BY a.debaser2_actor_type_id ";

  return debaser2_reports_execute_query($sql, $group, $param);

}

