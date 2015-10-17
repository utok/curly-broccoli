<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function proudtheme_form_system_theme_settings_alter(&$form, &$form_state) {
  require_once  DRUPAL_ROOT . '/' . drupal_get_path('theme', 'proudtheme') . '/includes/images.inc';
  proudtheme_add_inverted_logo($form, $form_state);
}
