<?php

namespace Drupal\mydrush\Helper;

use Drupal\node\Entity\Node;

Class NodeManager {

  /**
   * 
   * @param type $data
   */
  public function createNode($data) {
    if (!empty($data['title'])) {
      $values = [
        'type' => $data['type'],
        'status' => 1,
        'title' => $data['title'],
        'body' => [
          'value' => $data['body'],
          'format' => 'full_html',
        ],
        'uid' => 1
      ];
      $node = Node::create($values);
      $node->save();
      if ($nid = $node->id()) {
        return $this->getNodeUrl($nid);
      }
    }
    return FALSE;
  }

  private function getNodeUrl($nid = NULL) {
    global $base_url;
    $alias = '';
    if ($nid) {
      $alias = \Drupal::service('path.alias_manager')->getAliasByPath('/node/' . $nid);
    }
    return $base_url . $alias;
  }

}
