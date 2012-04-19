<?php
// $Id: open_flash_chart_api.admin.inc,v 1.1.2.1 2010/05/05 19:24:50 jvandervort Exp $


/**
 * @file
 * Contains all admin pages, settings, and validations.
 */

/**
 * Settings form for menu callback
 */
function open_flash_chart_api_settings() {

  // Old legacy default.
  $default_path = drupal_get_path('module', 'open_flash_chart_api');
  // But if they don't have the swf file loaded already, use a better default.
  if ( !file_exists($default_path . '/open-flash-chart.swf') ) {
    $default_path = 'sites/all/libraries/ofcv1';
  }

  $form['open_flash_chart_api_library_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to Open Flash Chart v1'),
    '#default_value' => variable_get('open_flash_chart_api_library_path', $default_path),
    '#size' => 55,
    '#maxlength' => 255,
    '#description' => t('This is the ofc library root directory.  It should contain both /open-flash-chart.swf and /js/swfobject.js and should be a path relative to the drupal install directory.'),
  );
  return system_settings_form($form);
}


function open_flash_chart_api_settings_validate($form, &$form_state) {
  // Test for finding the library files.
  if ( !file_exists($form_state['values']['open_flash_chart_api_library_path'] . '/open-flash-chart.swf') ) {
    form_set_error('open_flash_chart_api_library_path', t('Could not find open-flash-chart.swf in the libroot.'));
  }
  if ( !file_exists($form_state['values']['open_flash_chart_api_library_path'] . '/js/swfobject.js') ) {
    form_set_error('open_flash_chart_api_library_path', t('Could not find swfobject.js in the libroot/js directory.'));
  }
}
