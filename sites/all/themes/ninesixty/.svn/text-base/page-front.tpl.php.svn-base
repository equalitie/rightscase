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
      <?php if ($linked_logo_img): ?>
        <span id="logo" class="grid-1 alpha"><?php print $linked_logo_img; ?></span>
      <?php endif; ?>
      <?php if ($linked_site_name): ?>
      <!--  <h1 id="site-name" class="grid-3 omega"><?php print $linked_site_name; ?></h1>-->
      <?php endif; ?>
      
      </div>

    <?php if ($main_menu_links || $secondary_menu_links): ?>
      <div id="site-menu" class="grid-10">
      	<?php if($logged_in): ?>
	        <?php print $main_menu_links; ?>
	        
	        <?php print theme('links', menu_navigation_links('menu-top-menu',0)); ?>
		<?php endif; ?>
      </div>
    <?php endif; ?>

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
    <div id = "home-buttons">
	<?php if($logged_in): ?>
		
		<a href="node/add/case">
			<div id ="create_case_button" class = "home_button grid-4 alpha" ></div>
		</a>
		<a href="stats/individual_statistics">
			<div id ="stats_button" class = "home_button grid-4 alpha" ></div>
		</a>
		<a href="node">
			<div id ="recent_activity_button" class = "home_button grid-4 alpha" ></div>
		</a>
		<a href="node/1142">
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
