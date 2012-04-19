<?php
       // drupal_add_js('sites/all/modules/debaser2/swfobject/swfobject.js');
	drupal_add_css("sites/all/themes/ninesixty/styles/forms/stats_form.css");
	//drupal_add_js('sites/all/modules/debaser2/js/jquery.selectboxes.js');
	drupal_add_js('sites/all/modules/debaser2/js/jquery.field.js');
	

?>
<div class="stats-form-container grid-16 alpha omega">
	<div class="form-container grid-16">
		<div id="stats-form-left">
			<!--  ACTOR STATS -->
			<div class ='stats-form actor-form grid-5'>
				<div class = "stats-header actor">
					Actor Statistics
				</div>
				<div class="case-title">
					<!--<?php print drupal_render($form['chart_type']); ?>-->
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['field_type']); ?>
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['actor_type']); ?>
				</div>
			</div>
			<!-- CASE STATS -->
			
			<div class ='stats-form case-form grid-5'>
				<div class = "stats-header case">
					Case Statistics
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['case_options']); ?>
				</div>
				<div class="case-date">
					<div class="case-select">
						<?php print drupal_render($form['case_location_options']); ?>
					</div>
					<div class="case-radio">
						<input type="radio" name = "case-filters" value="0" id="location-radio"/>
					</div>
				</div>
				<div class="case-date clear-case">
					
					<div class="case-select">
						<?php print drupal_render($form['case_status_options']); ?>
					</div>
					<div class="case-radio">
						<input type="radio" name = "case-filters" value="1" id="status-radio"/>
					</div>
				</div>
				
			</div>
			<!-- VIOLATION STATS -->
			
			<div class ='stats-form vio-form grid-5'>
				<div class = "stats-header violation">
					Violation Statistics
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['violation_options']); ?>
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['violation_location_options']); ?>
				</div>
			</div>
			
			<!--
			<div class="case-date">	
				<?php print drupal_render($form['region']); ?>
			</div>-->
			<div class="case-region">	
				<div class="hide-field " style="display:none;">
					<?php /* assign the buttons to a variable */
						$buttons = drupal_render($form['submit']);
						//print drupal_render($form);
						/* print the rest of the form, which will be without buttons because we have already 'printed'
						* them when assigning them to the variable, and print the variable right after
						* the rest of the form
						*/

					?>
				</div>
					
			</div>
		</div>
		<div class="button-container grid-15">
                    <div class = "stats-button-holder">
                            <?php print $buttons; ?>
                    </div>
                </div>
            <div class="grid-4 suffix-12">
                <a href ="/print/stats/individual_statistics">
                    <?=t('Printer View'); ?>
                </a>
            </div>
	</div>
	
	
	<div class="graph-container grid-16 ">
		<?php $result =  $form['results']['#value'];
		//print $form['results']['#value'];
		//print $form['#children'];
		print drupal_render($form);
		?>
	</div>

</div>


