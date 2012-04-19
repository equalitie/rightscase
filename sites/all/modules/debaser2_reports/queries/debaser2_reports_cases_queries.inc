<?php

/**********************************

         CASE QUERIES

/*********************************/

/**
 *
 *
 */
function debaser2_reports_query_case_status_location($group = NULL, $location = NULL) {
  $result = debaser2_reports_query_case_status_location_sql($group, $location);
  while ($row = db_fetch_object($result)) {
    $results[$row->status][$row->location] = $row->count;
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_case_status_location_sql($group, $location){
  $sql = "SELECT COUNT({debaser2_case}.id) AS count, {debaser2_case_status}.title AS status, {debaser2_location}.title AS location
            FROM {debaser2_case}
            JOIN {debaser2_case_status}
              ON {debaser2_case_status}.id = {debaser2_case}.debaser2_case_status_id
            JOIN {debaser2_location}
              ON {debaser2_location}.id = {debaser2_case}.debaser2_location_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_case}.group_id = %d ";
  }

  if ($location) {
    $sql .= " AND {debaser2_case}.debaser2_location_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_case_status}.title, {debaser2_location}.title ";
  
  return debaser2_reports_execute_query($sql, $group, $location);
}

/**
 *
 *
 */
function debaser2_reports_query_case_status_status($group = NULL, $status = NULL) {
  $result = debaser2_reports_query_case_status_status_sql($group, $status);
  while ($row = db_fetch_object($result)) {
    $results[$row->status] = $row->count;
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_case_status_status_sql($group, $status){
  $sql = "SELECT COUNT({debaser2_case}.id) AS count, {debaser2_case_status}.title AS status
            FROM {debaser2_case}
            JOIN {debaser2_case_status}
              ON {debaser2_case_status}.id = {debaser2_case}.debaser2_case_status_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_case}.group_id = %d ";
  }

  if ($status) {
    $sql .= " AND {debaser2_case}.debaser2_case_status_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_case_status}.title ";

  return debaser2_reports_execute_query($sql, $group, $status);
}

/**
 *
 *
 */
function debaser2_reports_query_case_reason_location($group = NULL, $location = NULL) {
  $result = debaser2_reports_query_case_reason_location_sql($group, $location);
  while ($row = db_fetch_object($result)) {
    $results[$row->reason][$row->location] = $row->count;
  }
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_case_reason_location_sql($group, $location){
  $sql = "SELECT COUNT({debaser2_case}.id) AS count, {debaser2_case_intervention_reason}.title AS reason, {debaser2_location}.title AS location
            FROM {debaser2_case}
            JOIN {debaser2_case_intervention_reason}
              ON {debaser2_case_intervention_reason}.id = {debaser2_case}.debaser2_case_intervention_reason_id
            JOIN {debaser2_location}
              ON {debaser2_location}.id = {debaser2_case}.debaser2_location_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_case}.group_id = %d ";
  }

  if ($location) {
    $sql .= " AND {debaser2_case}.debaser2_location_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_case_intervention_reason}.title, {debaser2_location}.title ";
  return debaser2_reports_execute_query($sql, $group, $location);
}

/**
 *
 *
 */
function debaser2_reports_query_case_reason_status($group = NULL, $status = NULL) {
  $result = debaser2_reports_query_case_reason_status_sql($group, $status);
  while ($row = db_fetch_object($result)) {
    $results[$row->reason][$row->status] = $row->count;
  }
  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_case_reason_status_sql($group, $reason){
  $sql = "SELECT COUNT({debaser2_case}.id) AS count, {debaser2_case_intervention_reason}.title AS reason, {debaser2_case_status}.title AS status
            FROM {debaser2_case}
            JOIN {debaser2_case_intervention_reason}
              ON {debaser2_case_intervention_reason}.id = {debaser2_case}.debaser2_case_intervention_reason_id
            JOIN {debaser2_case_status}
              ON {debaser2_case_status}.id = {debaser2_case}.debaser2_case_status_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_case}.group_id = %d ";
  }

  if ($reason) {
    $sql .= " AND {debaser2_case}.debaser2_case_intervention_reason_id = %d ";
  }

  $sql .= " GROUP BY {debaser2_case_intervention_reason}.title , {debaser2_case_status}.title";

  return debaser2_reports_execute_query($sql, $group, $reason);
}


/**
 *
 *
 */
function debaser2_reports_query_case_date_location($group = NULL, $location = NULL) {
  $result = debaser2_reports_query_case_date_location_sql($group, $location);
  while ($row = db_fetch_object($result)) {
    $results[$row->month.'/'.$row->year][$row->location] = $row->count;
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_case_date_location_sql($group, $location){
  $sql = "SELECT COUNT({debaser2_case}.id) AS count, {debaser2_case_date}.month, {debaser2_case_date}.year, {debaser2_location}.title AS location
            FROM {debaser2_case}
            JOIN {debaser2_case_date}
              ON {debaser2_case_date}.id = {debaser2_case}.debaser2_case_date_id
            JOIN {debaser2_location}
              ON {debaser2_location}.id = debaser2_location_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_case}.group_id = %d ";
  }

  if ($location) {
    $sql .= " AND {debaser2_case}.debaser2_location_id = %d ";
  }

  $sql .= " AND (
                   ({debaser2_case_date}.month <= MONTH(CURDATE()) AND {debaser2_case_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_case_date}.month > MONTH(CURDATE()) AND {debaser2_case_date}.year = YEAR(CURDATE())-1)
                 )
           GROUP BY {debaser2_case_date}.year, {debaser2_case_date}.month, {debaser2_location}.title
           ORDER BY {debaser2_case_date}.year, {debaser2_case_date}.month ";

  return debaser2_reports_execute_query($sql, $group, $location);
}

/**
 *
 *
 */
function debaser2_reports_query_case_date_status($group = NULL, $status = NULL) {
  $result = debaser2_reports_query_case_date_status_sql($group, $status);
  while ($row = db_fetch_object($result)) {
    $results[$row->month.'/'.$row->year][$row->status] = $row->count;
  }

  return $results;
}

/**
 *
 *
 */
function debaser2_reports_query_case_date_status_sql($group, $status){
  $sql = "SELECT COUNT({debaser2_case}.id) AS count, {debaser2_case_date}.month, {debaser2_case_date}.year, {debaser2_case_status}.title AS status
            FROM {debaser2_case}
            JOIN {debaser2_case_date}
              ON {debaser2_case_date}.id = {debaser2_case}.debaser2_case_date_id
            JOIN {debaser2_case_status}
              ON {debaser2_case_status}.id = debaser2_case_status_id
           WHERE 1 = 1";

  if ($group) {
    $sql .= " AND {debaser2_case}.group_id = %d ";
  }

  if ($status) {
    $sql .= " AND {debaser2_case}.debaser2_case_status_id = %d ";
  }

  $sql .= " AND (
                   ({debaser2_case_date}.month <= MONTH(CURDATE()) AND {debaser2_case_date}.year = YEAR(CURDATE()))
                 OR
                   ({debaser2_case_date}.month > MONTH(CURDATE()) AND {debaser2_case_date}.year = YEAR(CURDATE())-1)
                 )
           GROUP BY {debaser2_case_date}.year, {debaser2_case_date}.month, {debaser2_case_status}.title
           ORDER BY {debaser2_case_date}.year, {debaser2_case_date}.month ";

  return debaser2_reports_execute_query($sql, $group, $status);
}

