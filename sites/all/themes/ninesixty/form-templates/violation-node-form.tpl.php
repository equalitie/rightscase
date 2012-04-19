<div class="clear-block"><!--~--></div>
<div class="case-node-form alpha grid-16">
  <div class="left-form-container grid-8 alpha">
    <div id="case-details-form-left">
      <div class="form-case">
        <?php print drupal_render($form['field_violation_perpetrator']); ?>
      </div>
      <div class="form-case">
        <?php print drupal_render($form['field_violation_victim']); ?>
      </div>

      <div class="form-case" style="display: none">
        <?php print drupal_render($form['field_case']); ?>
        <?php /*
        <script type="text/javascript">
          (function($) {
            $(function() {
               $('#edit-field-case-nid-nid').val('<?php print $case_id; ?>');
            });
          })(jQuery);
        </script>
        */ ?>
      </div>
      <div class="form-int-law left-case">
        <?php print drupal_render($form['taxonomy'][5]); ?>
        <div class="form-clear"><!--~--></div>
      </div>
      <div class="form-vio-type left-case">
        <?php //print drupal_render($form['taxonomy']['tags']); ?>
        <div id="taxonomy-tags-13" class="form-item">
          <?php print drupal_render($form['taxonomy'][13]); ?>
          
        </div>
        <div class="form-clear"><!--~--></div>
      </div>

      <div class="form-vio-date left-case input-text">
        <?php print drupal_render($form['field_vio_date']); ?>
        <div class="form-clear"><!--~--></div>
      </div>
      <div class="form-vio-province left-case">
        <?php print drupal_render($form['taxonomy'][3]); ?>
        <div class="form-clear"><!--~--></div>
      </div>
      <div class="case-gmap left-case">
        <?php //print drupal_render($form['field_map_ref']); ?>
        <div class="form-clear"><!--~--></div>
      </div>
    </div>
  </div>
  <div class="right-form-container grid-8 omega">
    <div id="case-details-form-right">
      <div class="form-testimony">
        <?php print drupal_render($form['field_chain_of_events']); ?>
      </div>
    </div>
    <div class="map_field" style="height: 520px; width: 100%"><!--~--></div>
    <input type="button" class="delete-marker" value="Delete selected marker"/>
  </div>
</div>
<div class="hide-field alpha grid-16" style="display:none;">
  <?php $buttons = drupal_render($form['buttons']); ?>
  <?php print drupal_render($form); ?>
</div>
<div class="report-field alpha grid-16">
  <?php print $buttons; ?>
</div>


