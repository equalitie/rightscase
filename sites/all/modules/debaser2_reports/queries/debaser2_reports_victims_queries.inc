<?php

/**
 *
 * The filter has to be "year" or "month" depending of what the user selected
 */
function debaser2_reports_query_victim_total_violation_age($group = NULL, $arg = null, $filter = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();
  $result = debaser2_reports_query_victim_total_violation_age_sql($group, $filter);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      if ($filter == 'year') {
        $results[$field][$row->year] = $row->$field;
      } elseif ($filter == 'month') {
        $results[$field][$row->month.'/'.$row->year] = $row->$field;
      } else {
        $results[$field] = $row->$field;    
      }
    }
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_victim_total_violation_age_sql($group, $filter) {
  $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more, 
                 {debaser2_violation_date}.year AS year, {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor}
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }
    
  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
    
  if ($filter == 'year') {
    $sql .= " GROUP BY {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= " GROUP BY {debaser2_violation_date}.year, {debaser2_violation_date}.month "; 
  }

  return debaser2_reports_execute_query($sql, $group, NULL);
}

/*
 * Created by Luis Fernando
 * Format Data of Victims x Ethnicity for Reports/Tests
 */
function debaser2_reports_query_victim_ethnicity_victims($group = NULL, $arg=null, $filter = NULL) {
  $results = array();
  $result  = debaser2_reports_query_victim_ethnicity_victims_sql($group, $filter);

  while ($row = db_fetch_object($result)) {
    if ($filter == 'year') {
      $results[$row->ethnicity][$row->year] = $row->count;
    } elseif ($filter == 'month') {
      $results[$row->ethnicity][$row->month.'/'.$row->year] = $row->count;
    } else {
      $results[$row->ethnicity] = $row->count;
    }
  }

  return $results;
}


/*
 * Created by Luis Fernando
 * Retrieve Data of Victims x Ethnicity for Reports/Tests
 */
function debaser2_reports_query_victim_ethnicity_victims_sql($group, $filter) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count, {debaser2_actor_ethnicity}.title AS ethnicity, {debaser2_violation_date}.year AS year, {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor}
            JOIN {debaser2_violation} 
              ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id )
            JOIN {debaser2_actor_ethnicity} 
              ON ( {debaser2_actor_ethnicity}.id = {debaser2_violation_actor}.debaser2_actor_ethnicity_id )
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_ethnicity}.title ";
  
  if ($filter == 'year') {
    $sql .= ", {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= ", {debaser2_violation_date}.year, {debaser2_violation_date}.month "; 
  }

  return debaser2_reports_execute_query($sql, $group, NULL);
}

/*
 * Created by Luis Fernando
 * Format Data of Victims x Political Afiliation for Reports/Tests
 */
function debaser2_reports_query_victim_political_affiliation_victims($group = NULL, $arg=NULL, $filter = NULL) {
  $results = array();
  $result  = debaser2_reports_query_victim_political_affiliation_victims_sql($group, $filter);

  while ($row = db_fetch_object($result)) {
    if ($filter == 'year') {
      $results[$row->political_affiliation][$row->year] = $row->count;
    } elseif ($filter == 'month') {
      $results[$row->political_affiliation][$row->month.'/'.$row->year] = $row->count;
    } else {
      $results[$row->political_affiliation] = $row->count;
    }
  }
  return $results;
}


/*
 * Created by Luis Fernando
 * Retrieve Data of Victims x Political Affiliation for Reports/Tests
 */
function debaser2_reports_query_victim_political_affiliation_victims_sql($group, $filter) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count, {debaser2_actor_political_affiliation}.title AS political_affiliation, {debaser2_violation_date}.year AS year, {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor}
            JOIN {debaser2_violation} 
              ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id  )
            JOIN {debaser2_actor_political_affiliation}
              ON ( {debaser2_actor_political_affiliation}.id = {debaser2_violation_actor}.debaser2_actor_political_affiliation_id )
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_political_affiliation}.title ";
  
  if ($filter == 'year') {
    $sql .= ", {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= ", {debaser2_violation_date}.year, {debaser2_violation_date}.month "; 
  }
  return debaser2_reports_execute_query($sql, $group, NULL);
}



/*
 * Created by Luis Fernando
 * Format Data of Victims x Gender for Reports/Tests
 */
function debaser2_reports_query_victim_gender_victims($group = NULL, $arg=NULL, $filter = NULL) {
  $results = array();
  $result  = debaser2_reports_query_victim_gender_victims_sql($group, $filter);

  while ($row = db_fetch_object($result)) {
    if ($filter == 'year') {
      $results[$row->gender][$row->year] = $row->count;
    } elseif ($filter == 'month') {
      $results[$row->gender][$row->month.'/'.$row->year] = $row->count;
    } else {
      $results[$row->gender] = $row->count;
    }
  }

  return $results;
}



/*
 * Created by Luis Fernando
 * Retrieve Data of Victims x Gender for Reports/Tests
 */
function debaser2_reports_query_victim_gender_victims_sql($group, $filter) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count, {debaser2_actor_gender}.title AS gender, {debaser2_violation_date}.year AS year, {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor}
            JOIN {debaser2_violation} 
              ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id  )
            JOIN {debaser2_actor_gender}
              ON ( {debaser2_actor_gender}.id = {debaser2_violation_actor}.debaser2_actor_gender_id )
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_gender}.title ";
  
  if ($filter == 'year') {
    $sql .= ", {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= ", {debaser2_violation_date}.year, {debaser2_violation_date}.month ";  
  }

  return debaser2_reports_execute_query($sql, $group, NULL);
}


/************************************************************************************

                    GENDER x AGE

/***********************************************************************************/

/**
 *
 *
 */
function debaser2_reports_query_victim_gender_by_age($group = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();
  $result = debaser2_reports_query_victim_gender_by_age_sql($group);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      $results[$field][$row->gender] = $row->$field;
    }
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_victim_gender_by_age_sql($group) {
  $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more, {debaser2_actor_gender}.title AS gender
            FROM {debaser2_violation_actor}
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_actor_gender}
              ON {debaser2_actor_gender}.id = {debaser2_violation_actor}.debaser2_actor_gender_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_actor_gender}.title ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}



/************************************************************************************

                    INTERNATIONAL STANDARDS

/***********************************************************************************/

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_age($group = NULL, $standard = NULL, $filter = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();

  $result = debaser2_reports_query_victim_international_standard_age_sql($group, $standard, $filter);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      if ($filter == 'year') {
        $results[$row->year][$field] = $row->$field;
      } elseif ($filter == 'month') {
        $results[$row->month.'/'.$row->year][$field] = $row->$field;
      } else {
        $results[$field] = $row->$field;
      }
      
    }
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_age_sql($group, $standard, $filter) {
     $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more, 
                 {debaser2_violation_international_standard}.title AS standard, 
                 {debaser2_violation_date}.year AS year, 
                 {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor}
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
  
  $sql .= " GROUP BY {debaser2_violation_international_standard}.title ";
  
  if ($filter == 'year') {
    $sql .= ", {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= ", {debaser2_violation_date}.year, {debaser2_violation_date}.month ";  
  }
  
  return debaser2_reports_execute_query($sql, $group, $standard);
}

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_ethnicity($group = NULL, $standard = NULL, $filter = NULL) {
  $results = array();
  $result = debaser2_reports_query_victim_international_standard_ethnicity_sql($group, $standard, $filter);
  
  while ($row = db_fetch_object($result)) {
    if ($filter == 'year') {
      $results[$row->ethnicity][$row->year] = $row->count;
    } elseif ($filter == 'month') {
      $results[$row->ethnicity][$row->month.'/'.$row->year] = $row->count;
    } else {
      $results[$row->ethnicity] = $row->count;
    }
  }
  
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_ethnicity_sql($group, $standard, $filter) {
  $sql = "SELECT COUNT({debaser2_violation_actor}.id) AS count, 
                 {debaser2_actor_ethnicity}.title AS ethnicity, 
                 {debaser2_violation_international_standard}.title AS standard, 
                 {debaser2_violation_date}.year AS year, 
                 {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor} 
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
            JOIN {debaser2_actor_ethnicity}
              ON {debaser2_actor_ethnicity}.id = {debaser2_violation_actor}.debaser2_actor_ethnicity_id
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";
  
  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }
  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_ethnicity}.title, {debaser2_violation_international_standard}.title ";
  
  if ($filter == 'year') {
    $sql .= ", {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= ", {debaser2_violation_date}.year, {debaser2_violation_date}.month ";  
  }
  
  return debaser2_reports_execute_query($sql, $group, $standard);
}

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_political_affiliation($group = NULL, $standard = NULL, $filter = NULL) {
  $results = array();
  $result = debaser2_reports_query_victim_international_standard_political_affiliation_sql($group, $standard, $filter);
  
  while ($row = db_fetch_object($result)) {
    if ($filter == 'year') {
      $results[$row->year][$row->political_affiliation] = $row->count;
    } elseif ($filter == 'month') {
      $results[$row->month.'/'.$row->year][$row->political_affiliation] = $row->count;
    } else {
      $results[$row->political_affiliation] = $row->count;
    }
  }
  
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_political_affiliation_sql($group, $standard, $filter) {
  $sql = "SELECT COUNT({debaser2_violation_actor}.id) AS count, 
                 {debaser2_actor_political_affiliation}.title AS political_affiliation, 
                 {debaser2_violation_international_standard}.title AS standard,
                 {debaser2_violation_date}.year AS year, 
                 {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor} 
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
            JOIN {debaser2_actor_political_affiliation}
              ON {debaser2_actor_political_affiliation}.id = {debaser2_violation_actor}.debaser2_actor_political_affiliation_id
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";
  
  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }
  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_political_affiliation}.title, {debaser2_violation_international_standard}.title ";
  
  if ($filter == 'year') {
    $sql .= ", {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= ", {debaser2_violation_date}.year, {debaser2_violation_date}.month ";  
  }
  
  return debaser2_reports_execute_query($sql, $group, $standard);
}

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_gender($group = NULL, $standard = NULL, $filter = NULL) {
  $results = array();
  $result = debaser2_reports_query_victim_international_standard_gender_sql($group, $standard, $filter);
  
  while ($row = db_fetch_object($result)) {
    if ($filter == 'year') {
      $results[$row->year][$row->gender] = $row->count;
    } elseif ($filter == 'month') {
      $results[$row->month.'/'.$row->year][$row->gender] = $row->count;
    } else {
      $results[$row->gender] = $row->count;
    }
  }
  
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_victim_international_standard_gender_sql($group, $standard, $filter) {
  $sql = "SELECT COUNT({debaser2_violation_actor}.id) AS count, 
                 {debaser2_actor_gender}.title AS gender, 
                 {debaser2_violation_international_standard}.title AS standard,
                 {debaser2_violation_date}.year AS year, 
                 {debaser2_violation_date}.month AS month
            FROM {debaser2_violation_actor} 
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
            JOIN {debaser2_actor_gender}
              ON {debaser2_actor_gender}.id = {debaser2_violation_actor}.debaser2_actor_gender_id
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";
  
  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }
  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  if ($filter == 'month') {
    $sql .= " AND (
                  ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 ) ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_gender}.title, {debaser2_violation_international_standard}.title ";
  
  if ($filter == 'year') {
    $sql .= ", {debaser2_violation_date}.year ";  
  } elseif ($filter == 'month') {
    $sql .= ", {debaser2_violation_date}.year, {debaser2_violation_date}.month ";  
  }
  
  return debaser2_reports_execute_query($sql, $group, $standard);
}




/**
 *
 *  VIOLATION TYPE x LOCATION Intermediate Function
 */
function debaser2_reports_query_violation_type_by_location($group = NULL, $param = NULL) {

  $results = array();
  $result = debaser2_reports_query_violation_type_by_location_sql($group, $param);

  while ($row = db_fetch_object($result)) {
    $results[$row->violation_type][$row->location] = $row->count;
  }

  return $results;
}

/**
 *
 *  VIOLATION TYPE x LOCATION Query Function
 */
function debaser2_reports_query_violation_type_by_location_sql($group, $param) {
  $sql = "SELECT count(v.id) AS count, t.title AS violation_type, l.title AS location
            FROM {debaser2_violation} v
            JOIN {debaser2_violation_type} t 
              ON (t.id = v.debaser2_violation_type_id)
            JOIN {debaser2_location} l 
              ON (l.id = v.debaser2_location_id)
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND v.group_id = %d ";
  }

  if ($param) {
    $sql .= " AND l.id = %d ";
  }

  $sql .= " GROUP BY t.title, l.title";

  return debaser2_reports_execute_query($sql, $group, $param);
}

/**
 *
 *  VIOLATION TYPE x POLITICAL AFFILIATION Intermediate Function
 */
function debaser2_reports_query_violation_type_by_political_affiliation($group = NULL, $param = NULL) {

  $results = array();
  $result = debaser2_reports_query_violation_type_by_political_affiliation_sql($group, $param);

  while ($row = db_fetch_object($result)) {
    $results[$row->violation_type][$row->political_affiliation] = $row->count;
  }

  return $results;
}


/**
 *
 *  VIOLATION TYPE x POLITICAL AFFILIATION Query Function
 */
function debaser2_reports_query_violation_type_by_political_affiliation_sql($group, $param) {
  $sql = "SELECT count(a.id) AS count, t.title AS violation_type, p.title AS political_affiliation
            FROM {debaser2_violation} v
            JOIN {debaser2_violation_actor} a 
              ON (a.debaser2_violation_id = v.id )
            JOIN {debaser2_violation_type} t 
              ON (t.id = v.debaser2_violation_type_id)
            JOIN {debaser2_actor_political_affiliation} p 
              ON (p.id = a.debaser2_actor_political_affiliation_id)
           WHERE a.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND v.group_id = %d ";
  }
  
  if ($param) {
    $sql .= " AND a.debaser2_actor_political_affiliation_id = %d ";
  }

  $sql .= " GROUP BY t.title, p.title ";

  return debaser2_reports_execute_query($sql, $group, $param);
}


/**
 *
 *  VIOLATION PERPETRATOR AGE x TOTAL VIOLATIONS Intermediate Function
 */
function debaser2_reports_query_perpetrator_age_by_total_violations($group = NULL, $param = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();
  $result = debaser2_reports_query_perpetrator_age_by_total_violations_sql($group, $param);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      $results[$field] = $row->$field;
    }
  }

  return $results;
}

/**
 *
 *  VIOLATION PERPETRATOR AGE x TOTAL VIOLATIONS Query Function
 */
function debaser2_reports_query_perpetrator_age_by_total_violations_sql($group, $param) {
  $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more
            FROM {debaser2_violation}
            JOIN {debaser2_violation_actor}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 2 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  return debaser2_reports_execute_query($sql, $group, $param);
}

