<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
drupal_add_js('sites/all/themes/ninesixty/js/actor-display/violation_display.js');

?>
<?php if($rows): ?>
<div class="sideTab vio-tab grid-3 alpha" >
    <div class="sideTabHeader vio-header">
        <h6><?php print t('Actors'); ?></h6>
    </div>


    <div class="sideTab-bottom">
        <ul class="view-cycle-pager grid-3" id="views-cycle-case_violations-page_1-nav">
            <?php print $rows; ?>
        </ul>
    </div>
</div>

<div id="violation-container" class="grid-13 omega">
    
</div>
<?php elseif($empty): ?>

  <!-- nothing added yet -->
	    <div class="view-empty grid-16 alpha">

	      <?php print $empty; ?>
	    </div>


<?php endif; ?>