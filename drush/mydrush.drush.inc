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
  // get content types
  $contentTypes = \Drupal::entityTypeManager()
      ->getStorage('node_type')
      ->loadMultiple();
  $types = [];
  foreach ($contentTypes as $contentType) {
    $types[$contentType->getOriginalId()] = $contentType->label();
  }
  if (!isset($type)) {
    $type = drush_choice($types, dt("Choose content type"));
  }
  if (empty($type)) {
    return drush_user_abort();
  }
  if (!isset($title)) {
    $title = drush_prompt("Enter node title", NULL, TRUE);
  }
  if (!isset($body)) {
    $body = drush_prompt("Enter node body", NULL, TRUE);
  }
  try {
    $data = ['type' => $type, 'title' => $title, 'body' => $body];
    $nodeManager = new NodeManager();
    if ($link = $nodeManager->createNode($data)) {
      return drush_log(dt('Node created with title !title, click on !link link to open.', ['!title' => $title, '!link' => $link]), 'success');
    }
  }
  catch (Exception $ex) {
    return drush_set_error('mydrush', dt('Something went wrong while creating node.'));
  }
}
