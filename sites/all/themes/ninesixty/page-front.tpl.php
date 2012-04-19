<?php
// $Id: page.tpl.php,v 1.1.2.1 2009/02/24 15:34:45 dvessel Exp $
	if (!$logged_in) {
		header('Location:/user');
	}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?> show-grid">
<div id="headerContent" class="clear-block">
  <div id="page" class="container-16 clear-block">

    <div id="site-header" class="clear-block">
      <div id="branding" class="grid-3 clear-block">
        <span id="logo" class="grid-1 alpha"><img src="/<?php echo $directory; ?>/images/rcase_SOFTWARE.png" alt="Home" title="Home" width="154" height="40"></span>
      <?php if ($linked_site_name): ?>
      <!--  <h1 id="site-name" class="grid-3 omega"><?php print $linked_site_name; ?></h1>-->
      <?php endif; ?>    
      </div>

    
      <div id="site-menu" class="grid-10">

	       <!-- <?php print $main_menu_links; ?>
	        
	        <?php print theme('links', menu_navigation_links('menu-top-menu',0)); ?>-->
		

      		        <!-- menu-->
  <ul class="links main-menu">
    <li class="menu-642 active-trail one first active"><a class="active" title="" href="/"><?=t('Home'); ?></a></li>
    <li class="menu-1765 two"><a title="<?=t('Search for Cases'); ?>" href="/cases"><?=t('Case Details'); ?></a></li>
    <li class="menu-2726 three"><a title="<?=t('Statistical analysis of data collected'); ?>" href="/stats/individual_statistics_new"><?=t('Analysis &amp; Statistics'); ?></a></li>
    <li class="menu-645 four"><a title="<?=t('View the most recently updated content in the application'); ?>" href="/activity/all"><?=t('Recent Activity'); ?></a></li>
    <li class="menu-4139 five last"><a title="<?=t('Debaser User Manual'); ?>" href="/node/1274"><?=t('Manual'); ?></a></li>
  </ul>	             

      </div>


    <?php if ($search_box): ?>
      <div id="search-box" class="grid-3"><?php print $search_box; ?></div>
    <?php endif; ?>
    </div>


    <div id="site-subheader" class="prefix-1 suffix-1 clear-block">
    <?php if ($mission): ?>
      <div id="mission" class="<?php print ns('grid-14', $header, 7); ?>">
        <?php print $mission; ?>
      </div>
    <?php endif; ?>

    <?php if ($header): ?>
      <div id="header-region" class="region <?php print ns('grid-14', $mission, 7); ?> clear-block">
        <?php //print $header; ?>
      </div>
    <?php endif; ?>
    </div>
	
</div>
</div>
<div id="tabsContent" class="clear-block">
	<div id="primary-tab-wrapper" class="container-16 clear-block">

					<div id="primary-tab-container">
						<div class="prmary-tabs-inner-wrapper">
							<div class="primary_tabs grid-11">
								<ul class="tabs primary">
									
									
								</ul>
							</div>
						</div>
						
						<div class="grid-5 omega case-name"></div>
					</div></div>	
	</div>
<div id="mainContent" class="clear-block">
	<div id="main-page" class="container-16 clear-block">
    <div id="main" class="column <?php print ns('grid-16', $left, 4, $right, 3) . ' ' . ns('push-4', !$left, 4); ?>">
		<div id="flash-detect">
		
		<noscript><?php print t('Please enable your javascript.')?></noscript>
		</div>
		
		
    <div id = "home-buttons">
	<?php if($logged_in): ?>
		
		<a href="node/add/case">
			<div id ="create_case_button" class = "home_button grid-4 alpha" ></div>
		</a>
		<a href="stats/individual_statistics_new">
			<div id ="stats_button" class = "home_button grid-4 alpha" ></div>
		</a>
		<a href="activity/all">
			<div id ="recent_activity_button" class = "home_button grid-4 alpha" ></div>
		</a>
		<a href="node/1274">
			<div id ="about_button" class = "home_button grid-4 alpha" ></div>
		</a>
		
	<?php endif; ?>
	</div>
  
	</div>
  </div>
  </div>

  <div id="footer" class="prefix-1 suffix-1">
    <?php if ($footer): ?>
      <div id="footer-region" class="region grid-14 clear-block">
        <?php print $footer; ?>
      </div>
    <?php endif; ?>

    <?php if ($footer_message): ?>
      <div id="footer-message" class="grid-14">
        <?php print $footer_message; ?>
      </div>
    <?php endif; ?>
  </div>


  
  
 
  <?php print $closure; 
  //drupal_rebuild_theme_registry();?>
</body>
</html>
