<?php 
function get_tag_cloud(){	
	return tagadelic_page_chunk();
}

/**
 * Get violation list
 * @return void
 */
function get_violation_list() {
  $sql = "SELECT
            t.tid, t.name, COUNT(tn.vid) num
          FROM
            {term_data} t
            JOIN {term_node} tn ON tn.tid = t.tid AND t.vid = %d
			JOIN {node} n ON n.vid = tn.vid AND n.status = 1
          GROUP BY
            t.tid
          ORDER BY
            t.name";

  $result = db_query(db_rewrite_sql($sql), 13);

  $tags = array();
  while ($data = db_fetch_object($result)) {
    $tags[] = $data;
  }

  return theme('violation_list', $tags);
}