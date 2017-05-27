<?php

use Drupal\mydrush\Helper\NodeManager;

/**
 * Implements hook_drush_command().
 */
function mydrush_drush_command() {
  $items = array();

  $items['create-node'] = array(
    'description' => 'Create node via drush.',
    'aliases' => ['cn', 'cdn'],
    'callback' => 'create_node',
    'options' => array(
      'type' => array(
        'description' => 'Enter node type',
      ),
      'title' => array(
        'description' => 'Enter node title',
      ),
      'body' => array(
        'description' => 'Enter node body',
      )
    ),
    'examples' => array(
      'drush cn --title=About us --body=<h3>Our organization</h3>' => '',
    ),
  );
  return $items;
}

/**
 * Call back function my_callback_drush_custom_drush_testing_demo()
 * The call back function name in the  following format
 *   drush_{module_name}_{item_id_for_command}()
 */
function create_node() {
  $type = drush_get_option('type');
  $title = drush_get_option('title');
  $body = drush_get_option('body');
  if (!$type) {
    $type = drush_prompt("Enter node type", NULL, TRUE);
  }
  if (!$title) {
    $title = drush_prompt("Enter node title", NULL, TRUE);
  }
  if (!$body) {
    $body = drush_prompt("Enter node body", NULL, TRUE);
  }
  try {
    $data = ['type' => $type, 'title' => $title, 'body' => $body];
    $nodeManager = new NodeManager();
    if ($nodeManager->createNode($data)) {
      return drush_log('Node created with title !title', ['!title' => $title], 'success');
    }
  }
  catch (Exception $ex) {
    return drush_set_error('mydrush', dt('Something went wrong while creating node.'));
  }
}
