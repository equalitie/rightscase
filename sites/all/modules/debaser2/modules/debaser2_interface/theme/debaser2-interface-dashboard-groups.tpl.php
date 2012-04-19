<?
/*
template file to provide links to the user add pages 

*/


?>
<? foreach($groups as $group): ?>
  <div class ='group-button' >
    <?= l( t('Add user to group : ') . $group->group_name, 'og/users/' . $group->nid . '/add_user'); ?>
  </div>
<? endforeach; ?>
