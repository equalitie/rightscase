<?php
// $Id: views-view-table.tpl.php,v 1.8 2009/01/28 00:43:43 merlinofchaos Exp $
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $class: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * @ingroup views_templates
 */
?>
<?php 

$i=0;
$j = 0;
$id_array = array();

function check_case_exists($cases_age, $term_id) {
	$i=0;
	foreach ($cases_age as $case) {
		if ($case['id']==$term_id)return $i;
		$i++;
	}
	return -1;
}
?>
<h6>Recent Activity</h6>
<div class = "grid-15 view-table">
<div id="tableContainer" class="tableContainer">
<table class="scrollTable">
  <?php if (!empty($title)) : ?>
    <caption><?php print $title; ?></caption>
  <?php endif; ?>
  <thead class="fixedHeader">
    <tr>
      <?php foreach ($header as $field => $label): ?>
	  	<?php if(!$i==0): ?>
        	<th class="views-field views-field-<?php print $fields[$field]; ?>">
        		<?php print $label; ?>
        	</th>
		<?php else: ?>
			<?php $i++; ?>
		<?php endif; ?>
		
      <?php endforeach; ?>
    </tr>
  </thead>
  <tbody class="scrollContent">
    <?php foreach ($rows as $count => $row): ?>
		<?php $i=0; ?>
      	<tr class="<?php print implode(' ', $row_classes[$count]); ?>">
        	<?php foreach ($row as $field => $content): ?>
				<?php if(!$i==0): ?>
          			<td class="views-field views-field-<?php print $fields[$field]; ?>">
           				<?php print $content; ?>
	          		</td>
					
				<?php else: ?>
					<?php 
					// check if this case has been printed yet or not
					if(check_case_exists($id_array, $row['nid'])==-1){
						$id_array[$j]['id'] = $row['nid'];
						$j++;
						$i++;
					}else{
						break;
					}
					 ?>
				<?php endif; ?>	
	        <?php endforeach; ?>
	      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
</div></div>
