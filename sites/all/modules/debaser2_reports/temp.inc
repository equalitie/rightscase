<?php

/**************************************

                QUERIES

**************************************/

/**
 *
 */
function debaser2_reports_victims_functions( $field_type, $filter_type, $func_type ){
  $query_functions = array(
    'total_violations' => array(
      'age' => array(
        'query' => 'debaser2_reports_query_violation_total_violation_age',
        'format' => '',
        'display' => ''
      ),

      'ethnicity' => array(
        'query' => 'debaser2_reports_query_violation_ethnicity_victims',
        'format' => '',
        'display' => ''
      ),

       'political_affiliation' => array(
        'query' => 'debaser2_reports_query_violation_political_affiliation_victims',
        'format' => '',
        'display' => ''
      ),

      'gender' => array(
        'query' => 'debaser2_reports_query_violation_gender_victims',
        'format' => '',
        'display' => ''
      ),


    ),
    'years' => array(
      'age' => array(
        'query' => 'debaser2_reports_query_violation_years_age',
        'format' => '',
        'display' => ''
      ),

      'ethnicity' => array(
        'query' => 'debaser2_reports_query_violation_years_ethnicity',
        'format' => '',
        'display' => ''
      ),

      'gender' => array(
        'query' => 'debaser2_reports_query_violation_years_gender',
        'format' => '',
        'display' => ''
      ),

      'political_affiliation' => array(
        'query' => 'debaser2_reports_query_violation_years_political_affiliation',
        'format' => '',
        'display' => ''
      ),
    ),

    'international_standards' => array(
      'age' => array(
        'query' => 'debaser2_reports_query_violation_international_standard_age',
        'format' => '',
        'display' => ''
      ),
      'ethnicity' => array(
        'query' => 'debaser2_reports_query_violation_international_standard_ethnicity',
        'format' => '',
        'display' => ''
      ),
      'gender' => array(
        'query' => 'debaser2_reports_query_violation_international_standard_gender',
        'format' => '',
        'display' => ''
      ),
      'political_affiliation' => array(
        'query' => 'debaser2_reports_query_violation_international_standard_political_affiliation',
        'format' => '',
        'display' => ''
      ),
    ),

  );

  return $query_functions[$field_type][$filter_type][$func_type];
}










function debaser2_reports_query_violation_total_violation_age($group = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();
  $result = debaser2_reports_query_violation_total_violation_age_sql($group);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      $results[$field][$row->status] = $row->$field;
    }
  }

  return $results;
}

function debaser2_reports_query_violation_total_violation_age_sql($group) {
  $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more, {debaser2_case_status}.title AS status
            FROM {debaser2_violation_actor}
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_case_status}
              ON {debaser2_case_status}.id = {debaser2_violation}.debaser2_violation_case_status_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_violation}.debaser2_violation_case_status_id ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}












function debaser2_reports_query_violation_years_age($group = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();
  $result = debaser2_reports_query_violation_years_age_sql($group);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      $results[$field][$row->year] = $row->$field;
    }
  }

  return $results;
}

function debaser2_reports_query_violation_years_age_sql($group) {
  $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more, {debaser2_violation_date}.year AS year
            FROM {debaser2_violation_actor}
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = {debaser2_violation}.debaser2_violation_date_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_violation_date}.year ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}






function debaser2_reports_query_violation_international_standard_age($group = NULL, $standard = NULL) {
  $fields = array('age_0_18', 'age_19_35', 'age_36_54', 'age_55_more');
  $results = array();

  $result = debaser2_reports_query_violation_international_standard_age_sql($group, $standard);

  while ($row = db_fetch_object($result)) {
    foreach($fields as $field) {
      $results[$field][$row->standard] = $row->$field;
    }
  }

  return $results;
}

function debaser2_reports_query_violation_international_standard_age_sql($group, $standard) {
     $sql = "SELECT SUM(age_0_18) AS age_0_18, SUM(age_19_35) AS age_19_35, SUM(age_36_54) AS age_36_54, SUM(age_55_more) AS age_55_more, 
                 {debaser2_violation_international_standard}.title AS standard
            FROM {debaser2_violation_actor}
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  $sql .= " GROUP BY {debaser2_violation_international_standard}.title ";
  
  return debaser2_reports_execute_query($sql, $group, $standard);
}





function debaser2_reports_query_violation_international_standard_ethnicity($group = NULL, $standard = NULL) {
  $results = array();
  $result = debaser2_reports_query_violation_international_standard_ethnicity_sql($group, $standard);
  
  while ($row = db_fetch_object($result)) {
    $results[$row->ethnicity][$row->standard] = $row->count;
  }
  
  return $results;
}

function debaser2_reports_query_violation_international_standard_ethnicity_sql($group, $standard) {
  $sql = "SELECT COUNT({debaser2_violation_actor}.id) AS count, {debaser2_actor_ethnicity}.title AS ethnicity, {debaser2_violation_international_standard}.title AS standard
            FROM {debaser2_violation_actor} 
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
            JOIN {debaser2_actor_ethnicity}
              ON {debaser2_actor_ethnicity}.id = {debaser2_violation_actor}.debaser2_actor_ethnicity_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";
  
  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }
  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_ethnicity}.title, {debaser2_violation_international_standard}.title ";
  
  return debaser2_reports_execute_query($sql, $group, $standard);
}






function debaser2_reports_query_violation_international_standard_political_affiliation($group = NULL, $standard = NULL) {
  $results = array();
  $result = debaser2_reports_query_violation_international_standard_political_affiliation_sql($group, $standard);
  
  while ($row = db_fetch_object($result)) {
    $results[$row->political_affiliation][$row->standard] = $row->count;
  }
  
  return $results;
}

function debaser2_reports_query_violation_international_standard_political_affiliation_sql($group, $standard) {
  $sql = "SELECT COUNT({debaser2_violation_actor}.id) AS count, {debaser2_actor_political_affiliation}.title AS political_affiliation, {debaser2_violation_international_standard}.title AS standard
            FROM {debaser2_violation_actor} 
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
            JOIN {debaser2_actor_political_affiliation}
              ON {debaser2_actor_political_affiliation}.id = {debaser2_violation_actor}.debaser2_actor_political_affiliation_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";
  
  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }
  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_political_affiliation}.title, {debaser2_violation_international_standard}.title ";
  
  return debaser2_reports_execute_query($sql, $group, $standard);
}





function debaser2_reports_query_violation_international_standard_gender($group = NULL, $standard = NULL) {
  $results = array();
  $result = debaser2_reports_query_violation_international_standard_gender_sql($group, $standard);
  
  while ($row = db_fetch_object($result)) {
    $results[$row->gender][$row->standard] = $row->count;
  }
  
  return $results;
}

function debaser2_reports_query_violation_international_standard_gender_sql($group, $standard) {
  $sql = "SELECT COUNT({debaser2_violation_actor}.id) AS count, {debaser2_actor_gender}.title AS gender, {debaser2_violation_international_standard}.title AS standard
            FROM {debaser2_violation_actor} 
       LEFT JOIN {debaser2_violation}
              ON {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id
            JOIN {debaser2_violation_international_standard}
              ON {debaser2_violation_international_standard}.id = {debaser2_violation}.debaser2_violation_international_standard_id
            JOIN {debaser2_actor_gender}
              ON {debaser2_actor_gender}.id = {debaser2_violation_actor}.debaser2_actor_gender_id
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";
  
  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }
  
  if ($standard) {
    $sql .= " AND {debaser2_violation}.debaser2_violation_international_standard_id = %d ";
  }
  
  $sql .= " GROUP BY {debaser2_actor_gender}.title, {debaser2_violation_international_standard}.title ";
  
  return debaser2_reports_execute_query($sql, $group, $standard);


/*
 * Created by Luis Fernando
 * Format Data of Victims x Ethnicity for Reports/Tests
 */
function debaser2_reports_query_violation_ethnicity_victims($group = NULL) {
  $results = array();
  $result  = debaser2_reports_query_violation_ethnicity_victims_sql($group);

  while ($row = db_fetch_object($result)) {
      $results[$row->ethnicity] = $row->count;
  }

  return $results;
}


/*
 * Created by Luis Fernando
 * Retrieve Data of Victims x Ethnicity for Reports/Tests
 */
function debaser2_reports_query_violation_ethnicity_victims_sql($group) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count,
                 {debaser2_actor_ethnicity}.title AS ethnicity
            FROM {debaser2_violation_actor}
      INNER JOIN {debaser2_violation} ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id )
      INNER JOIN {debaser2_actor_ethnicity} ON ( {debaser2_actor_ethnicity}.id = {debaser2_violation_actor}.debaser2_actor_ethnicity_id )
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= "   GROUP BY {debaser2_actor_ethnicity}.title ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}

/*
 * Created by Luis Fernando
 * Format Data of Victims x Political Afiliation for Reports/Tests
 */
function debaser2_reports_query_violation_political_affiliation_victims($group = NULL) {
  $results = array();
  $result  = debaser2_reports_query_violation_political_affiliation_victims_sql($group);

  while ($row = db_fetch_object($result)) {
      $results[$row->political_affiliation] = $row->count;
  }

  return $results;
}


/*
 * Created by Luis Fernando
 * Retrieve Data of Victims x Political Affiliation for Reports/Tests
 */
function debaser2_reports_query_violation_political_affiliation_victims_sql($group) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count,
                 {debaser2_actor_political_affiliation}.title AS political_affiliation
            FROM {debaser2_violation_actor}
      INNER JOIN {debaser2_violation} ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id  )
      INNER JOIN {debaser2_actor_political_affiliation}
              ON ( {debaser2_actor_political_affiliation}.id = {debaser2_violation_actor}.debaser2_actor_political_affiliation_id )
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_actor_political_affiliation}.title ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}



/*
 * Created by Luis Fernando
 * Format Data of Victims x Gender for Reports/Tests
 */
function debaser2_reports_query_violation_gender_victims($group = NULL) {
  $results = array();
  $result  = debaser2_reports_query_violation_gender_victims_sql($group);

  while ($row = db_fetch_object($result)) {
      $results[$row->gender] = $row->count;
  }

  return $results;
}



/*
 * Created by Luis Fernando
 * Retrieve Data of Victims x Gender for Reports/Tests
 */
function debaser2_reports_query_violation_gender_victims_sql($group) {
  $sql = "		  SELECT count({debaser2_violation_actor}.id) AS count,
                 {debaser2_actor_gender}.title AS gender
            FROM {debaser2_violation_actor}
      INNER JOIN {debaser2_violation} ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id  )
      INNER JOIN {debaser2_actor_gender}
              ON ( {debaser2_actor_gender}.id = {debaser2_violation_actor}.debaser2_actor_gender_id )
           WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= "     GROUP BY {debaser2_actor_gender}.title ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}


/*
 * Created by Luis Fernando
 * Retrieve Data of Year x Ethnicity for Reports/Tests
 */
function debaser2_reports_query_violation_years_ethnicity($group = NULL){
  $results = array();
  $result  = debaser2_reports_query_violation_years_ethnicity_sql($group);

  while ($row = db_fetch_object($result)) {
      $results[$row->year][$row->ethnicity] = $row->count;
  }

  return $results;
}



/*
 * Created by Luis Fernando
 * Retrieve Data of Year x Ethnicity for Reports/Tests
 */
function debaser2_reports_query_violation_years_ethnicity_sql($group) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count, {debaser2_violation_date}.year as year, {debaser2_actor_ethnicity}.title as ethnicity
            FROM {debaser2_violation_actor}
      INNER JOIN {debaser2_violation} ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id  )
      INNER JOIN {debaser2_actor_ethnicity} ON ( {debaser2_actor_ethnicity}.id = {debaser2_violation_actor}.debaser2_actor_ethnicity_id  )
      INNER JOIN {debaser2_violation_date} ON ( {debaser2_violation_date}.id = {debaser2_violation}.debaser2_violation_date_id )
		       WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_violation_date}.year, {debaser2_actor_ethnicity}.title ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}



/*
 * Created by Luis Fernando
 * Retrieve Data of Year x Gender for Reports/Tests
 */
function debaser2_reports_query_violation_years_gender($group = NULL){
  $results = array();
  $result  = debaser2_reports_query_violation_years_gender_sql($group);

  while ($row = db_fetch_object($result)) {
      $results[$row->year][$row->gender] = $row->count;
  }

  return $results;
}



/*
 * Created by Luis Fernando
 * Retrieve Data of Year x Gender for Reports/Tests
 */
function debaser2_reports_query_violation_years_gender_sql($group) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count, {debaser2_violation_date}.year as year, {debaser2_actor_gender}.title as gender
            FROM {debaser2_violation_actor}
      INNER JOIN {debaser2_violation} ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id  )
      INNER JOIN {debaser2_actor_gender} ON ( {debaser2_actor_gender}.id = {debaser2_violation_actor}.debaser2_actor_gender_id  )
      INNER JOIN {debaser2_violation_date} ON ( {debaser2_violation_date}.id = {debaser2_violation}.debaser2_violation_date_id )
		       WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_violation_date}.year, {debaser2_actor_gender}.title ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}




/*
 * Created by Luis Fernando
 * Retrieve Data of Year x Political Affiliation for Reports/Tests
 */
function debaser2_reports_query_violation_years_political_affiliation($group = NULL){
  $results = array();
  $result  = debaser2_reports_query_violation_years_political_affiliation_sql($group);

  while ($row = db_fetch_object($result)) {
      $results[$row->year][$row->political_affiliation] = $row->count;
  }

  return $results;
}



/*
 * Created by Luis Fernando
 * Retrieve Data of Year x Political Affiliation for Reports/Tests
 */
function debaser2_reports_query_violation_years_political_affiliation_sql($group) {
  $sql = "SELECT count({debaser2_violation_actor}.id) AS count, {debaser2_violation_date}.year as year, {debaser2_actor_political_affiliation}.title as political_affiliation
            FROM {debaser2_violation_actor}
      INNER JOIN {debaser2_violation} ON ( {debaser2_violation_actor}.debaser2_violation_id = {debaser2_violation}.id  )
      INNER JOIN {debaser2_actor_political_affiliation} ON ( {debaser2_actor_political_affiliation}.id = {debaser2_violation_actor}.debaser2_actor_political_affiliation_id  )
      INNER JOIN {debaser2_violation_date} ON ( {debaser2_violation_date}.id = {debaser2_violation}.debaser2_violation_date_id )
		       WHERE {debaser2_violation_actor}.debaser2_actor_type_id = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_violation_date}.year, {debaser2_actor_political_affiliation}.title ";

  return debaser2_reports_execute_query($sql, $group, NULL);
}

