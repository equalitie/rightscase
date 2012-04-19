<?php

/*
 *
 * Prepare data to be used in tests and reports
 */
function debaser2_reports_query_violation_case_status($group = NULL, $location = NULL) {
  $result = debaser2_reports_query_violation_case_status_sql($group, $location);
  while ($row = db_fetch_object($result)) {
    $results[$row->status][$row->location] = $row->count;
  }

  return $results;
}



/*
 *
 * Retrieve data to be used in tests and reports
 */
function debaser2_reports_query_violation_case_status_sql($group, $location) {
  $sql = "SELECT COUNT({debaser2_violation}.id) AS count, {debaser2_case_status}.title AS status, {debaser2_location}.title AS location
            FROM {debaser2_violation}
            JOIN {debaser2_case_status}
              ON {debaser2_case_status}.id = {debaser2_violation}.debaser2_violation_case_status_id
            JOIN {debaser2_location}
              ON {debaser2_location}.id = {debaser2_violation}.debaser2_location_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  if ($location) {
    $sql .= " AND {debaser2_violation}.debaser2_location_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_case_status}.title, {debaser2_location}.title ";

  return debaser2_reports_execute_query($sql, $group, $location);
}

/*
 *
 * Prepare data to be used in tests and reports
 */
function debaser2_reports_query_violation_month($group = NULL, $location = NULL) {
  $result = debaser2_reports_query_violation_month_sql($group, $location);
  while ($row = db_fetch_object($result)) {
    $results[$row->location][$row->month.'/'.$row->year] = $row->count;
  }

  return $results;
}



/*
 *
 * Retrieve data to be used in tests and reports
 */
function debaser2_reports_query_violation_month_sql($group, $location) {

  $sql = "SELECT COUNT({debaser2_violation}.id) AS count, {debaser2_violation_date}.month, {debaser2_violation_date}.year, {debaser2_location}.title AS location
            FROM {debaser2_violation}
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = {debaser2_violation}.debaser2_violation_date_id
            JOIN {debaser2_location}
              ON {debaser2_location}.id = {debaser2_violation}.debaser2_location_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  if ($location) {
    $sql .= " AND {debaser2_violation}.debaser2_location_id = %d ";
  }

  $sql .= " AND (
                   ({debaser2_violation_date}.month <= MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_violation_date}.month > MONTH(CURDATE()) AND {debaser2_violation_date}.year = YEAR(CURDATE())-1)
                 )
           GROUP BY {debaser2_location}.title, {debaser2_violation_date}.year, {debaser2_violation_date}.month
           ORDER BY {debaser2_violation_date}.year, {debaser2_violation_date}.month ";

  return debaser2_reports_execute_query($sql, $group, $location);
}


/*
 *
 * Prepare data to be used in tests and reports
 */
function debaser2_reports_query_violation_year($group = NULL, $location = NULL) {
  $result = debaser2_reports_query_violation_year_sql($group, $location);
  while ($row = db_fetch_object($result)) {
    $results[$row->location][$row->year] = $row->count;
  }

  return $results;
}



/*
 *
 * Retrieve data to be used in tests and reports
 */

function debaser2_reports_query_violation_year_sql($group, $location) {

  $sql = "SELECT COUNT({debaser2_violation}.id) AS count, {debaser2_violation_date}.year, {debaser2_location}.title AS location
            FROM {debaser2_violation}
            JOIN {debaser2_violation_date}
              ON {debaser2_violation_date}.id = {debaser2_violation}.debaser2_violation_date_id
            JOIN {debaser2_location}
              ON {debaser2_location}.id = {debaser2_violation}.debaser2_location_id
           WHERE 1 = 1 ";

  if ($group) {
    $sql .= " AND {debaser2_violation}.group_id = %d ";
  }

  if ($location) {
    $sql .= " AND {debaser2_violation}.debaser2_location_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_location}.title, {debaser2_violation_date}.year
            ORDER BY {debaser2_violation_date}.year";

  return debaser2_reports_execute_query($sql, $group, $location);
}
