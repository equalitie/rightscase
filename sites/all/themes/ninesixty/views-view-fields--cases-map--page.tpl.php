<?php $data = array('title' => $row->node_node_data_field_case_title); ?>
<?php $markers = @unserialize($row->node_data_field_vio_date_field_markers_value); ?>
<?php $chain_of_events = $fields['field_chain_of_events_value']->content; ?>
<?php ob_start(); ?>
<p>
  <strong><?php echo $fields['title_1']->content; ?></strong>
  <br />
  <strong>Case:</strong> <?php echo l($row->node_node_data_field_case_title, 'cases/' . $row->node_node_data_field_case_nid); ?>
  <br />
  <strong>Violation Date:</strong> <?php echo $fields['field_vio_date_value']->content; ?>
  <br />
  <strong>International Standard: </strong> <?php echo $fields['tid_2']->content; ?>
  <?php if (isset($fields['tid_3'])): ?>
  <br />
  <strong>Violation Type: </strong> <?php echo $fields['tid_3']->content; ?>
  <?php endif; ?>
  <br />
  <?php echo $fields['tid']->content; ?>
</p>
<?php $data['content'] = ob_get_clean(); ?>
<?php if (!empty($markers) && is_array($markers)): ?>
  <?php foreach ($markers as $marker): ?>
    <?php $_marker = array_merge($data, array('coords' => $marker)); ?>
    <script type="text/javascript">statMarker.push(<?php echo json_encode($_marker); ?>);</script>
  <?php endforeach; ?>
<?php endif; ?>