<?php /* ?>
<form action="<?php print $form['#action']; ?>" method="post"></form>
*/ ?>
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
        <script type="text/javascript">
          (function($) {
            $(function() {
               $('#edit-field-case-nid-nid').val('<?php print $caseid; ?>');
            });
          })(jQuery);
        </script>
      </div>
      <div class="form-int-law left-case">
        <?php print drupal_render($form['taxonomy'][5]); ?>
        <div class="form-clear"><!--~--></div>
      </div>
      <div class="form-vio-type left-case">
        <?php //print drupal_render($form['taxonomy']['tags']); ?>
        <div id="taxonomy-tags-13" class="form-item">
          <label for="taxonomy[tags][13]">
            Violation Type:
            <span title="This field is required." class="form-required">*</span>
          </label>
          <select name="taxonomy[tags][13]" id="taxonomy[tags][13]">
          <?php
            $sql = "SELECT * FROM {term_data} WHERE vid = %d";
            $result = db_query(db_rewrite_sql($sql), 13);
            $terms = array();
            while ($data = db_fetch_object($result)) {
              print '<option value="' . $date->tid . '">' . $data->name . '</option>';
            }
          ?>
          </select>
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
        <?php print drupal_render($form['field_map_ref']); ?>
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
  </div>
</div>
<div class="hide-field alpha grid-16" style="display:none;">
  <?php $buttons = drupal_render($form['buttons']); ?>
  <?php print drupal_render($form); ?>
</div>
<div class="report-field alpha grid-16">
  <?php print $buttons; ?>
</div>

