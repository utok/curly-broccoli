<?php
/**
 * Implements template_process_panels_add_content_modal().
 */
function proudtheme_preprocess_panels_add_content_modal(&$variables) {
  // @todo: do we need this instead (for permissions?)

  // Process the list of categories.
  $variables['categories_array'] = array();
  foreach ($variables['categories'] as $key => $category_info) {
    // 'root' category is actually displayed under the categories, so
    // skip it.
    if ($key == 'root') {
      continue;
    }

    $class = 'panels-modal-add-category btn btn-sm btn-default';
    if ($key == $variables['category']) {
      $class .= ' active';
    }

    $title = '<i class="fa fa-fw ' . $category_info['icon'] . '"></i> ' . $category_info['title'];

    $url = $variables['renderer']->get_url('select-content', $variables['region'], $key);
    $variables['categories_array'][] = ctools_ajax_text_button($title, $url, '', $class);
  }

}

/**
 * Implements template_process_panels_add_content_modal().
 */
function proudtheme_process_panels_add_content_modal(&$variables) {

  $variables['content'] = !empty($variables['categories'][$variables['category']]['content']) ? $variables['categories'][$variables['category']]['content'] : array();

  foreach ($variables['content'] as $key => $item) {
    
    $variables['content'][$key]['rendered'] = theme('panels_add_content_link', array(
      'renderer' => $variables['renderer'], 
      'region' => $variables['region'], 
      'content_type' => $item,
    ));
  }

}


/**
 * Implements template_preprocess_panels_add_content_link().
 */
function proudtheme_preprocess_panels_add_content_link(&$vars) {
  $vars['title'] = filter_xss_admin($vars['content_type']['title']);
  $vars['description'] = isset($vars['content_type']['description']) ? $vars['content_type']['description'] : $vars['title'];
  $vars['icon'] = ctools_content_admin_icon($vars['content_type']);
    if (empty($vars['renderer'])) {
    //dpm($vars);
  }
  else {
    $vars['url'] = $vars['renderer']->get_url('add-pane', $vars['region'], $vars['content_type']['type_name'], $vars['content_type']['subtype_name']);
  }

  $title = '<i class="fa '. !empty($vars['fa_icon']) ? $vars['fa_icon'] : 'fa-sticky-note' .' fa-3x"></i>';
  $title .= '<h6>'. $vars['title'] .'</h6>';

  $button_classes = 'panels-modal-add-config card card-block text-center card-btn';
  $vars['button'] = ctools_ajax_text_button($title, $vars['url'], $vars['description'], $button_classes);

}