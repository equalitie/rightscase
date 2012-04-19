<table cellpadding="0" cellspacing="0" border="0" width="100%" class="zebra">
  <?php $index = 1; foreach ($tags as $tag): ?>
  <tr class="<?php echo $index++ % 2 ? 'odd' : 'even' ;?>">
    <td>
      <?php echo l($tag->name, 'taxonomy/term/' . $tag->tid); ?>
    </td>
    <td>
      <strong><?php echo $tag->num; ?></strong>
    </td>
  </tr>
  <?php endforeach; ?>
</table>