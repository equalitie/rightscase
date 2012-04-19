<?php 
if($_SERVER['HTTPS']){ 
  $prefix = 'https';
}else{
  $prefix = 'http';
}
?>
<li class ="violation-pager <?php print $fields['nid_1']->content; ?>">
    <a href="<?php echo $prefix; ?>://<?php print $_SERVER['HTTP_HOST'].'/vioLoader/'.$fields['nid_1']->content.'/'.$fields['nid']->content; ?>/vio_page">
        <?php print $fields['field_vio_date_value']->content; ?>
    </a>
</li>


