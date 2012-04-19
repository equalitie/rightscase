<?php
$my_url = $url;
$my_snippet = $snippet;
$my_info = $info;
$id = strtok($url, '/');
while($id=strtok('/'))$return_id=$id;
$node = node_load($return_id);
switch($node_type = $info_split['type']){
	case $node_type=='Actor':
		echo '<a href="/cases/'.$node->field_case[0]['nid'].'/actors/'.strtolower($node->taxonomy[3]->name).'">';
		echo $node->field_actor_name[0]['value'].'</a>';
		
		
		break;
	case $node_type=='Violation':
		echo '<a href="/cases/'.$node->field_case[0]['nid'].'/violations">';
		echo $node->title.'</a>';
		
		break;
	case $node_type=='Case':
		echo '<a href="/cases/'.$node->nid.'">';
		echo $node->title.'</a>';
		break;
	
}
?>
<?php if ($snippet) : ?>
    <p class="search-snippet"><?php print $snippet; ?></p>
  <?php endif; ?>
<?php

echo '<br/><br/>';