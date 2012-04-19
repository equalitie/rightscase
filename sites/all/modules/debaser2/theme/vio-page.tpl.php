<?php

/*
write out all our variables to nice easy to read format

*/
foreach ($violation as $variable => $value){
  $$variable = $value;
}
/*
Available Variables

$perps            - comma separated list of perpetrators
$vio_tags         - violation tag
$standard         - international standard
$region           - region where violation was committed
$date             - date of start of violation
$dateTo           - date of end of violation
$case_id          - case id
$chain_of_events  - chain of evaents textarea content,
$location         - array of location fields
$nid              - violation node id

*/


?>

<div id="violation-container" class="grid-13 omega">
	<div class ="left-violation-content alpha grid-6">

		<div class="violation-details grid-6">
		<div class="vio-field-wrapper alpha grid-6">
			<div class="violation-details-label alpha omega grid-3">
				<?php print t('Violation Type') ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $vio_tags; ?>
			</div>
		</div>
		<div class="vio-field-wrapper alpha grid-6">
			<div class="violation-details-label alpha omega grid-3">
				<?php print t('International Law'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $standard; ?>
			</div>
		</div>
		<div class="vio-field-wrapper alpha grid-6">
			<div class="violation-details-label alpha omega grid-3">
				<?php print t('Location'); ?> :
			</div>
			<div class="violation-details-content  omega grid-3">
				<?php print $region; ?>
			</div>
		</div>
		<div class="vio-field-wrapper alpha grid-6">
			<div class="violation-details-label alpha omega grid-3">
				<?php print t('Violation Start Date'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $date; ?>
			</div>
		</div>
		<div class="vio-field-wrapper alpha grid-6">
			<div class="violation-details-label alpha omega grid-3">
				<?php print t('Violation End Date'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $dateTo; ?>
			</div>
		</div>
		<!-- victims -->
		<div class="vio-field-wrapper alpha grid-6">
			<div class="violation-details-label alpha omega grid-3">
				<?php print t('Victims'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $victims; ?>
			</div>
		</div>
		<!-- perps -->
		<div class="vio-field-wrapper alpha grid-6">
			<div class="violation-details-label alpha omega grid-3">
				<?php print t('Perpetrators'); ?> :
			</div>
			<div class="violation-details-content omega grid-3">
				<?php print $perps; ?>
			</div>
		</div>
		
		
    <div id="mapholder" class="vio-field-wrapper alpha omega grid-6">

    </div>

	</div>

	</div>
	<div class ="right-actor-content omega grid-7">
		<div class="testimony-header"><?php print t('Chain of Events') ?></div>
		<div class="violation-textarea"><?php print $chain_of_events; ?></div>


		<div class="button-holder">
			<div class="edit-button">
				<a class="button" href="<?php print $base_url; ?>/node/<?php echo $nid; ?>/edit?destination=<?php print urlencode('cases/'.$case_id.'/violations'); ?>" >
                                    <span><?=t('Edit Violation'); ?></span>
                                </a>
			</div>
			<div class="edit-button ">
                            <a class="button" href="<?php print $base_url; ?>/node/add/violation?destination=<?php print urlencode('cases/'.$case_id.'/violations'); ?>" >
                                <span><?=t('Add Violation'); ?></span></a>
			</div>
			<div class="edit-button ">
				<a class="button" href="<?php print $base_url; ?>/print<?php print $_SERVER['REDIRECT_URL']; ?>" target="_blank">
					<span><?=t('Printer View'); ?></span>
				</a>
			</div>
		</div>

	</div>
</div>
