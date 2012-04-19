<div class="case-node-form alpha grid-16">
	<div class="left-form-container grid-4 alpha">
		<div id="stats-form-left">
			
			<div class="case-title">
				<?php print drupal_render($form['chart_type']); ?>
			</div>
			<div class="case-date">	
				<?php print drupal_render($form['primary_field_type']); ?>
			</div>
			<div class="case-date">	
				<?php print drupal_render($form['location']); ?>
			</div>
			<div class="case-date">	
				<?php print drupal_render($form['secondary_field_type']); ?>
			</div>
			
			<div class="case-date">	
				<?php print drupal_render($form['region']); ?>
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
					<?php print $buttons; ?>
			</div>
			
		</div>
		
	</div>
		
	
	<div class="right-form-container grid-12 omega">
		<?php $result =  $form['results']['#value'];
		//print $form['results']['#value'];
		//print $form['#children'];
		print drupal_render($form);
		?>
	</div>

</div>


