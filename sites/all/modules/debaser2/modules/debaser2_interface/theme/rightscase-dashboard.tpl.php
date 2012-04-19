<?php
?>

<div class='groups-totals grid-8 alpha' >
  <h1> Group Total Cases </h1>
  <? foreach ($groups['groups'] as $group): ?>
    <p class='dash-text'><?=$group['name'] ?> : <?=$group['total'] ?> cases</p>   
  <? endforeach ?>
    <p class='dash-text'>Total cases : <?=$groups['overall_total'] ?> cases</p>   
</div>
<div class = 'activity grid-8 omega' >
  <h1> Recent Activity </h1>
  <?=$activity ?>
</div>
