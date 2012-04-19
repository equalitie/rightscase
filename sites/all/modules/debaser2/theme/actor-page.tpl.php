
<?php
/*
write out all our variables to nice easy to read format

*/

foreach ($actor as $variable => $value){
  $$variable = $value;
}
/*
Available Variables

  $ethnicity        - 
  $affiliation 
  $type             - victim / perp / witness
  $dateOB           - date of birth
  $dateOD           - date of death
  $files 
  $img_path 
  $nid              - node id of the actor
  $gender 
  $age 
  $contact_details 
  $body             - testimony
  $outcome 
  $case_id          - case nid for referring case
*/
?>
<div id="actor-container" class="grid-13 omega">
<div class ="left-content alpha grid-2">

    <?php if( $img_path ): ?>

        
        <div class="actor-photo ">
            <img src="https://<?php print $img_path; ?>" alt="actor photo" />
        </div>

    <?php endif;?>

</div>
<div class="right-side grid-11 omega">
	<div class="actor-table-spacer grid-11"></div>

	<div class="actor-details-table alpha grid-5">
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Name'); ?>:
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $title; ?>
			</div>
		</div>
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha  grid-2">
				<?php print t('Date of Birth'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $dateOB; ?>
			</div>
		</div>
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha  grid-2">
				<?php print t('Date Of Death'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $dateOD; ?>
			</div>
		</div>
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Gender'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $gender ?>
			</div>
		</div>
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Affiliation'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $affiliation; ?>
			</div>
		</div>
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('State'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $state; ?>
			</div>
		</div>
	</div>
	<div class="actor-details-table  grid-5">
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Non State'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $nonState ?>
			</div>
		</div>

		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Ethnicity'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $ethnicity; ?>
			</div>
		</div>

		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Age'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $age ?>
			</div>
		</div>
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('ID Type'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $id_type ?>
			</div>
		</div>
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Number'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $id_number ?>
			</div>
		</div>
		
		<div class="vio-field-wrapper grid-5">
			<div class="violation-details-label alpha grid-2">
				<?php print t('Contact Details'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $contact_details; ?>
			</div>
		</div>

	</div>
<!--	<div class ="right-actor-content grid-10">
		<div class="actor-table-spacer grid-10"></div>


	</div>-->

</div>

</div>
<div id="files-container" class="grid-13">
<div class="right-side">


	<div class ="right-actor-table alpha grid-5">
		<div class="testimony-header"><?= t('Files'); ?></div>
		<div class="testimony-textarea"><?php print $files; ?></div>
	</div>
	</div>
	<div class ="right-actor-table omega grid-8">
	<div class="testimony-header"><?php print t('Testimony'); ?></div>
	<div class="testimony-textarea"><?php print $body; ?></div>
	</div>
        <?php if($type=='Victim'):?>
            <div class="testimony-header">><?= t('Expected Outcome'); ?></div>
            <div class ="testimony-textarea grid-12 alpha omega">
                <?php print $outcome ?>
            </div>
        <?php endif;?>
	<div class = "button-holder grid-10">



		<div class="edit-button  ">
			<?php
			/*
			if(stristr($type, 'applicant'))$actor_type = 'applicant';
			else if(stristr($type, 'perpetrator'))$actor_type = 'perpetrator';
			else if(stristr($type, 'witness'))$actor_type = 'witness';
                        else if(stristr($type, 'victim'))$actor_type = 'victim';
                        */

			?>
			<a class="button" href="<?php print $base_url; ?>/node/<?php echo $nid; ?>/edit?destination=<?php print urlencode("cases/".$case_id."/actors/".$actor_type); ?>" >
                            <span><?= t('Edit'); ?>
				<?php
					if(!$actor_type)$actor_type = 'victim';
					print ucfirst($actor_type); ?>
                            </span>
			</a>
		</div>
		<div class="edit-button ">
                    <a class="button" href="<?php print $base_url; ?>/node/add/actor?destination=<?php print urlencode("cases/".$case_id."/actors/".$actor_type); ?>" >
                            <span><?= t('Add'); ?>
				<?php
					if(!$actor_type)$actor_type = 'victim';
					print ucfirst($actor_type); ?></span>
			</a>
		</div>
		<div class="edit-button ">
			<a class="button" href="<?php print $base_url; ?>/print<?php print $_SERVER['REDIRECT_URL']; ?>" target="_blank">
				<span><?= t('Printer View'); ?></span>
			</a>
		</div>

	</div>

</div>
