<?php

/**
 * Implementation of hook_rules_defaults().
 */
function debaser2_features_update_case_status_rules_defaults() {
  return array(
    'rules' => array(
      'rules_execute_my_vbo' => array(
        '#type' => 'rule',
        '#set' => 'event_cron',
        '#label' => 'execute my vbo',
        '#active' => 1,
        '#weight' => '-5',
        '#categories' => array(
          '0' => 'case status',
          'debaser2_features_update_case_status' => 'debaser2_features_update_case_status',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'act as admin user',
              'label callback' => FALSE,
              'module' => 'PHP',
              'eval input' => array(
                '0' => 'code',
              ),
            ),
            '#name' => 'rules_action_custom_php',
            '#settings' => array(
              'code' => 'global $user,$original_user;
$original_user = $user;
$old_state = session_save_session();
session_save_session(FALSE); // D7: use drupal_save_session(FALSE);
$user = user_load(array(\'uid\' => 1));   // The uid of user that will run the rule.',
              'vars' => array(
                '0' => 'user',
              ),
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'code' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
          '1' => array(
            '#type' => 'action',
            '#settings' => array(
              'view_vid' => '60',
              'operation_key' => 'views_bulk_operations_taxonomy_action:7f88f7f1e14ee5c9f82f417dc6120588',
              'operation_arguments' => '',
              'view_exposed_input' => '',
              'view_arguments' => '',
              '#argument map' => array(
                'object' => 'user',
              ),
            ),
            '#name' => 'views_bulk_operations_action_user',
            '#info' => array(
              'label' => 'Execute a VBO programmatically on user',
              'arguments' => array(
                'object' => array(
                  'type' => 'user',
                  'label' => 'Object',
                ),
              ),
              'module' => 'Views Bulk Operations',
              'eval input' => array(),
              'base' => 'rules_core_action_execute',
              'action_name' => 'views_bulk_operations_action',
              'configurable' => TRUE,
            ),
            '#weight' => 0,
          ),
          '2' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'act as original user',
              'label callback' => FALSE,
              'module' => 'PHP',
              'eval input' => array(
                '0' => 'code',
              ),
            ),
            '#name' => 'rules_action_custom_php',
            '#settings' => array(
              'code' => 'global $user,$original_user;
$user = $original_user;
session_save_session($old_state);',
              'vars' => array(
                '0' => 'user',
              ),
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'code' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function debaser2_features_update_case_status_views_api() {
  return array(
    'api' => '2',
  );
}
