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
			<div class ='stats-form victims-form grid-5'>
				<div class = "stats-header victims">
					Victims Statistics
				</div>
				<div class="case-title">
					<!--<?php print drupal_render($form['chart_type']); ?>-->
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['violation_victim_options']); ?>
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['violation_actor_options']); ?>
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['int_standard']); ?>
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['date_options']); ?>
				</div>
			</div>
			
			<!--  political affiliation STATS -->
			<div class ='stats-form political_affiliation-form grid-5'>
				<div class = "stats-header political_affiliation">
					Political Affiliation Statistics
				</div>
				<div class="case-title">
					<!--<?php print drupal_render($form['chart_type']); ?>-->
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['political_affiliation_options']); ?>
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['political_affiliation']); ?>
				</div>
			</div>
			
			<!--  others STATS -->
			<div class ='stats-form other-form grid-5'>
				<div class = "stats-header others-stats">
					Other Statistics
				</div>
				<div class="case-title">
					<!--<?php print drupal_render($form['chart_type']); ?>-->
				</div>
				<div class="case-date">	
					<?php print drupal_render($form['other_statistics']); ?>
				</div>
			</div>
			
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


