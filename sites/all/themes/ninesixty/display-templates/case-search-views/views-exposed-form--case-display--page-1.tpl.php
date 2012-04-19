<?php
// $Id: views-exposed-form.tpl.php,v 1.4 2008/05/07 23:00:25 merlinofchaos Exp $
/**
* @file views-exposed-form.tpl.php
*
* This template handles the layout of the views exposed filter form.
*
* Variables available:
* - $widgets: An array of exposed form widgets. Each widget contains:
* - $widget->label: The visible label to print. May be optional.
* - $widget->operator: The operator for the widget. May be optional.
* - $widget->widget: The widget itself.
* - $button: The submit button for the form.
*
* @ingroup views_templates
*/
global $user;
?>
<?php if (!empty($q)): ?>
	<?php
// This ensures that, if clean URLs are off, the 'q' is added first so that
// it shows up first in the URL.
		print $q;
		
	?>
<?php endif; ?>



<div class="grid_16 clear-block">
	<div class="grid-8 alpha case-search-left ">
		
		<div class="grid-3 alpha case-search-label">
			<?php print $widgets['filter-title']->label; ?>: 
		</div>
		<div class="grid-5 case-search-textfield">
			<?php print $widgets['filter-title']->widget; ?>
		</div>
	</div>
<?php if (sizeof($user->og_groups)>1): ?>
	<div class="grid-8 case-search-right omega">
		<div class="grid-3 alpha case-search-label">
			<?php print $widgets['filter-group_nid']->label; ?>: 
		</div>
		<div class="grid-5 case-search-textfield">
			<?php print $widgets['filter-group_nid']->widget; ?>
		</div>
	</div>
<?php endif; ?>
	<div class="grid-8 alpha case-search-left ">
		<div class="grid-3 alpha case-search-label">
			<?php print $widgets['filter-body']->label; ?>: 
		</div>
		<div class="grid-5 case-search-textfield">
			<?php print $widgets['filter-body']->widget; ?>
		</div>
		
	</div>
	<div class="grid-8 case-search-right omega">
		<div class="grid-3 alpha case-search-label">
			<?php print $widgets['filter-field_user_uid']->label; ?>: 
		</div>
		<div class="grid-5 case-search-textfield">
			<?php print $widgets['filter-field_user_uid']->widget; ?>
		</div>
	</div>
		<div class="grid_16 clear-block">
		<div class="case-search-button">
			<?php print $button ?>
		</div>
	</div>

</div>
