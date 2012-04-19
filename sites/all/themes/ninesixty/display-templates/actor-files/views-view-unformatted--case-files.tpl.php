<?php
// $Id: views-view-unformatted.tpl.php,v 1.6 2008/10/01 20:52:11 merlinofchaos Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */

?>
<div class = "fileTableContainer">
	<table class="file-table">
	 	<thead class="fileFixedHeader">
	 		<tr>
				<th><?=t('Actor Name'); ?></th><th><?=t('File Name'); ?></th><th><?=t('File Type'); ?></th><th><?=t('Size'); ?></th><th><?=t('Description'); ?></th>
			</tr>
		</thead>
		<tbody class = "fileScrollContent">
			<?php foreach ($rows as $id => $row): ?>
				<?php print $row; ?>
			<?php endforeach; ?>
		</tbody>
	</table>
</div>
