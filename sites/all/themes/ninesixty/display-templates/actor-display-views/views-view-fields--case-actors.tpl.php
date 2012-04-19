<?php 
if($_SERVER['HTTPS']){ 
  $prefix = 'https';
}else{
  $prefix = 'http';
}
?>
<li class ="violation-pager <?php print $fields['nid_1']->content; ?>">
    <a href="<?php echo $prefix; ?>://<?php print $_SERVER['HTTP_HOST'].'/actorLoader/'.$fields['nid_1']->content.'/'.$fields['nid']->content; ?>/actor_page">
        <?php print $fields['field_actor_name_value']->content; ?>
    </a>
</li>


