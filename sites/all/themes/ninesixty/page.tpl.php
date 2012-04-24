<?php
// $Id: page.tpl.php,v 1.1.2.1 2009/02/24 15:34:45 dvessel Exp $
global $base_url;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
  <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <?php print $scripts; ?>
	<script type="text/javascript" src="http://maps.google.com/maps/api/js?sensor=false"></script>

  </head>

  <body class="<?php print $body_classes; ?> show-grid">

    
    <div id="headerContent" class="clear-block">
      <div id="page" class="container-16 clear-block">

        <div id="site-header" class="clear-block">
          <div id="branding" class="grid-3 clear-block">
            <span id="logo" class="grid-1 alpha"><img src="/<?php echo $directory; ?>/images/rcase_SOFTWARE.png" alt="Home" title="Home" width="154" height="40"></span>
            <?php if ($linked_site_name): ?>
            <!--<h1 id="site-name" class="grid-3 omega"><?php print $linked_site_name; ?></h1>-->
            <?php endif; ?>

          </div>
          <? //TODO figure out why the menu isn't working ?>
          <!--<?php if ($main_menu_links || $secondary_menu_links): ?>
          <div id="site-menu" class="grid-10">
          <?php if ($logged_in): ?>
          <?php print $main_menu_links; ?>

          <?php print theme('links', menu_navigation_links('menu-top-menu', 0)); ?>
          <?php endif; ?>
          </div>
          <?php endif; ?>-->
          <div class="grid-10" id="site-menu">
          <!-- menu-->
          <ul class="links main-menu"><li class="menu-642 active-trail one first active"><a class="active" title="" href="/"><?=t('Home'); ?></a></li>
            <li class="menu-1765 two"><a title="" href="/cases"><?=t('Case Details'); ?></a></li>
            <li class="menu-2726 three"><a title="Statistical analysis of data collected" href="/stats/individual_statistics_new"><?=t('Analysis &amp; Statistics'); ?></a></li>
            <li class="menu-645 four"><a title="View the most recently updated content in the application" href="/activity/all"><?=t('Recent Activity'); ?></a></li>
            <li class="menu-4139 five last"><a title="Debaser User Manual" href="/rightscase/manual"><?=t('Manual'); ?></a></li>
          </ul>	        
          </div>

        <?php if ($search_box): ?>
          <div id="search-box" class="grid-3">
            <?php print $search_box; ?>
          </div>
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
    <div class="container-16">
      <?php if ($messages): ?>
        <?php print $messages; ?>
      <?php endif; ?>
    </div>
    
    <div id="tabsContent" class="">
    <?php if ($tabs && $tabs != '</div>'): ?>
    <?php print $tabs; ?>

    <?php elseif ($tabs == '</div>' || !$tabs): ?>
    <?php
    $vars = explode('/', $_GET['destination']);
    $my_node = node_load($vars[1]);
    $case_name = $my_node->title;
    $case_class = 'active';
    switch ($vars[2]) {
    case 'actors':
    $actor_class = 'active';
    $case_class = '';
    $processing_class = '';
    $report_class = '';
    $violations_class = '';
    break;
    case 'violations':
    $actor_class = '';
    $case_class = '';
    $processing_class = '';
    $report_class = '';
    $violations_class = 'active';
    break;

    case 'report':
    $actor_class = '';
    $case_class = '';
    $processing_class = '';
    $report_class = 'active';
    $violations_class = '';
    break;
    }
    ?>
    <div id="primary-tab-wrapper" class="container-16 clear-block">

    <div id="primary-tab-container">
    <div class="prmary-tabs-inner-wrapper">
    <div class="primary_tabs grid-11">
    <ul class="tabs primary">
    <?php
    if (!$vars[1]) {
    print "<!--"; //comment out tabs if in create case
    } ?>
    <li class="<?php print $case_class; ?>"><a href="<?php print $base_url; ?>/cases/<?php print $vars[1]; ?>"><span></span>Details</a></li>

    <li class="<?php print $actor_class; ?>"><a href="<?php print $base_url; ?>/cases/<?php print $vars[1]; ?>/actors"><span></span>Actors</a></li>
    <li class="<?php print $violations_class; ?>"><a href="<?php print $base_url; ?>/cases/<?php print $vars[1]; ?>/violations"><span></span>Violations</a></li>

    <li ><a href="<?php print $base_url; ?>/cases/<?php print $vars[1]; ?>/files"><span></span>Files</a></li>

    <li class="<?php print $report_class; ?>"><a href="<?php print $base_url; ?>/cases/<?php print $vars[1]; ?>/report"><span></span>Report</a></li>
    <?php
    if (!$vars[1]) {
    print "-->";
    } ?>

    </ul>
    </div>
    </div>

    <div class="grid-5 omega case-name"><h6> <?php if ($case_name
    )print "Case: " . $case_name; ?></h6></div>
    </div></div>
    <?php endif; ?>
    </div>

    <div id="mainContent" class="">
    <div id="main-page" class="container-16 clear-block">
    <div id="main" class="column <?php print ns('grid-16', $left, 4, $right, 3) . ' ' . ns('push-4', !$left, 4); ?>">
    <?php //print $breadcrumb; ?>
    <?php if ($title): ?>
    <h1 class="title" id="page-title"><?php //6501616 print $title; ?></h1>
    <?php endif; ?>


    <?php print $help; ?>
    <div id="main-content" class="region clear-block">
    <?php print $content; ?>
    </div>
    <div class="grid-15">
    <?php print $case_list_footer; ?>
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

    <?php if ($case_list_footer): ?>
    <div id="footer-message" class="grid-14">


    </div>
    <?php endif; ?>
    </div>

    <?php if ($my_admin_links): ?>

      <div id="footer-region" class="region grid-14 clear-block">
      <?php print $my_admin_links; ?>
      </div>
    <?php endif; ?>

    <?php print $closure; ?>


  </body>
</html>
