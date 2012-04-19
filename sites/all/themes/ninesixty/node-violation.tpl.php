<?php
// $Id: node.tpl.php,v 1.5 2007/10/11 09:51:29 goba Exp $
// get the case name
$case = node_load($node->field_case[0]['nid']);
$violation_type = null;
$int_standard = "";
// get the international standard
foreach ($node->taxonomy as $tag) {
  if ($tag->vid == 5) {
    $int_standard = $tag->name;
  }
  if ($tag->vid == 13) {
    $violation_type = $tag->name;
  }
}
?>
<div id="node-<?php print $node->nid; ?>">
  <h2><?php  print $title ?></h2>
  <b>Case:</b><a
  href="http://<?php print $_SERVER['HTTP_HOST'] . '/cases/' . $node->field_case[0]['nid'] . '/violations' ?>"><?php print $case->title; ?></a>
  <br/>
  <b>Violation Type: </b> <?php print $violation_type; ?>
  <br />
  <b>Violation Date:</b> <?php print $node->field_vio_date[0]['view']; ?>
  <br/>
  <b>International Standard:</b> <?php print $int_standard; ?>
  <br/>
</div>
