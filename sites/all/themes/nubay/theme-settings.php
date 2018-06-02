<?php
/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function nubay_form_system_theme_settings_alter(&$form, &$form_state) {
  $enable_extensions = isset($form_state['values']['enable_extensions']);
  if (($enable_extensions && $form_state['values']['enable_extensions'] == 1) || (!$enable_extensions && $form['at-settings']['extend']['enable_extensions']['#default_value'] == 1)) {
    nubay_color_styles_form($form, $form_state);
    nubay_inline_block_form($form, $form_state);
  }
}

/**
 * @param $form
 * @param $form_state
 */
function nubay_color_styles_form(&$form, &$form_state) {
  $foreground_elements = array(
    'html' => 'html',
    'body' => 'body',
    'h1.node-title, h1.node-title a' => 'Node Title',
    '.sf-menu.sf-style-none li a' => 'Superfish menu item',
    'h1' => 'h1',
    'h2' => 'h2',
    'h3' => 'h3',
    'h4' => 'h4',
    'h5' => 'h5',
    'h6' => 'h6',
    'a' => 'a',
    'a:visted' => 'a:visited',
    'a:hover' => 'a:hover',
  );

  $background_elements = array(
    'html' => 'html',
    'body' => 'body',
    '.sf-menu.sf-style-none li a.active' => 'Superfish active menu item',
    '.sf-menu.sf-style-none li a:hover' => 'Superfish menu item hover',
  );
  // primary color
  $form['at']['nubaystyles_primary_color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Primary Color'),
    '#description' => t('<h3>Primary Colors</h3><p>Setting styles for the theme via the AT infrastructure</p>'),
  );
  $form['at']['nubaystyles_primary_color']['primary_color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Primary Color'),
    '#description' => t('<h3>Primary Color</h3><p>Set the primary color for the site, and choose what elements it applies for.</p>'),
  );

  $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('<strong>Enable Primary Color</strong>'),
    '#return' => 1,
    '#default_value' => theme_get_setting('nubay_primary_color_enable'),
  );

  $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color'] = array(
    '#type' => 'textfield',
    '#title' => t('<strong>Primary Color</strong>'),
    '#default_value' => theme_get_setting('nubay_primary_color'),
  );

  if (module_exists('color_field')) {
    drupal_add_js(libraries_get_path('bgrins-spectrum') . '/spectrum.js');
    drupal_add_css(libraries_get_path('bgrins-spectrum') . '/spectrum.css');
    $spectrum_js = 'jQuery(".spectrum-color-picker").spectrum({
        showInput: true,
        allowEmpty: true,
        showAlpha: true,
        showInitial: true,
        showInput: true,
        preferredFormat: "rgb",
        clickoutFiresChange: true,
        showButtons: false
      });';
    drupal_add_js($spectrum_js, array('type' => 'inline', 'scope' => 'footer'));
    $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color']['#attributes'] = array('class' => array('spectrum-color-picker'));
  }

  $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color_elements_foreground'] = array(
    '#type' => 'select',
    '#title' => t('Primary Color Elements - Foreground'),
    '#description' => t('Choose which elements should receive the primary color.'),
    '#multiple' => TRUE,
    '#default_value' => theme_get_setting('nubay_primary_color_elements_foreground'),
    '#options' => $foreground_elements,
  );

  $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color_elements_background'] = array(
    '#type' => 'select',
    '#title' => t('Primary Color Elements - Background'),
    '#description' => t('Choose which elements should receive the primary color as a background.'),
    '#multiple' => TRUE,
    '#default_value' => theme_get_setting('nubay_primary_color_elements_background'),
    '#options' => $background_elements,
  );

  $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color_additional_foreground'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional Selectors - Foreground'),
    '#description' => t('Enter a comma separated list of css selectors that should receive the primary color for the text color. Do not include a comma at the end.'),
    '#default_value' => theme_get_setting('nubay_primary_color_additional_foreground'),
  );

  $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color_additional_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional Selectors - Background'),
    '#description' => t('Enter a comma separated list of css selectors that should receive the primary color for the background color. Do not include a comma at the end.'),
    '#default_value' => theme_get_setting('nubay_primary_color_additional_background'),
  );

  $form['at']['nubaystyles_primary_color']['primary_color']['nubay_primary_color_use_important'] = array(
    '#type' => 'checkbox',
    '#return' => 1,
    '#title' => 'Use !important',
    '#description' => t('Use !important css keyword for all primary color element styling'),
    '#default_value' => theme_get_setting('nubay_primary_color_use_important'),
  );
  // secondary color
  $form['at']['nubaystyles_secondary_color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Secondary Color'),
    '#description' => t('<h3>Secondary Colors</h3><p>Setting styles for the theme via the AT infrastructure</p>'),
  );
  $form['at']['nubaystyles_secondary_color']['secondary_color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Secondary Color'),
    '#description' => t('<h3>Secondary Color</h3><p>Set the secondary color for the site, and choose what elements it applies for.</p>'),
  );

  $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('<strong>Enable Secondary Color</strong>'),
    '#return' => 1,
    '#default_value' => theme_get_setting('nubay_secondary_color_enable'),
  );

  $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color'] = array(
    '#type' => 'textfield',
    '#title' => t('<strong>Secondary Color</strong>'),
    '#default_value' => theme_get_setting('nubay_secondary_color'),
  );

  if (module_exists('color_field')) {
    drupal_add_js(libraries_get_path('bgrins-spectrum') . '/spectrum.js');
    drupal_add_css(libraries_get_path('bgrins-spectrum') . '/spectrum.css');
    $spectrum_js = 'jQuery(".spectrum-color-picker").spectrum({
        showInput: true,
        allowEmpty: true,
        showAlpha: true,
        showInitial: true,
        showInput: true,
        preferredFormat: "rgb",
        clickoutFiresChange: true,
        showButtons: false
      });';
    drupal_add_js($spectrum_js, array('type' => 'inline', 'scope' => 'footer'));
    $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color']['#attributes'] = array('class' => array('spectrum-color-picker'));
  }

  $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color_elements_foreground'] = array(
    '#type' => 'select',
    '#title' => t('Secondary Color Elements - Foreground'),
    '#description' => t('Choose which elements should receive the secondary color.'),
    '#multiple' => TRUE,
    '#default_value' => theme_get_setting('nubay_secondary_color_elements_foreground'),
    '#options' => $foreground_elements,
  );

  $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color_elements_background'] = array(
    '#type' => 'select',
    '#title' => t('Secondary Color Elements - Background'),
    '#description' => t('Choose which elements should receive the secondary color as a background.'),
    '#multiple' => TRUE,
    '#default_value' => theme_get_setting('nubay_secondary_color_elements_background'),
    '#options' => $background_elements,
  );

  $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color_additional_foreground'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional Selectors - Foreground'),
    '#description' => t('Enter a comma separated list of css selectors that should receive the secondary color for the text color. Do not include a comma at the end.'),
    '#default_value' => theme_get_setting('nubay_secondary_color_additional_foreground'),
  );

  $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color_additional_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Additional Selectors - Background'),
    '#description' => t('Enter a comma separated list of css selectors that should receive the secondary color for the background color. Do not include a comma at the end.'),
    '#default_value' => theme_get_setting('nubay_secondary_color_additional_background'),
  );

  $form['at']['nubaystyles_secondary_color']['secondary_color']['nubay_secondary_color_use_important'] = array(
    '#type' => 'checkbox',
    '#return' => 1,
    '#title' => 'Use !important',
    '#description' => t('Use !important css keyword for all secondary color element styling'),
    '#default_value' => theme_get_setting('nubay_secondary_color_use_important'),
  );

  $form['#submit'][] = 'nubay_color_styles_theme_settings_submit';
}


/**
 * Form submit handler for the nubay theme settings additions
 *
 * @see nubay_form_system_theme_settings_alter()
 *
 * @param $form
 * @param $form_state
 */
function nubay_color_styles_theme_settings_submit(&$form, &$form_state) {
  // Set form_state values into one variable
  $values = $form_state['values'];

  // Get the active theme name, $theme_key will return the admin theme
  $theme_name = $form_state['build_info']['args'][0];

  // Set the path variable to the right path
  if ($values['global_files_path'] === 'public_files') {
    $path = 'public://adaptivetheme/' . $theme_name . '_files';
  }
  elseif ($values['global_files_path'] === 'theme_directory') {
    $path = drupal_get_path('theme', $theme_name) . '/generated_files';
  }
  elseif ($values['global_files_path'] === 'custom_path') {
    $path = $values['custom_files_path'];
  }

  // $styles_data holds all data for the stylesheet
  $styles_data = [];

  if (!empty($values['nubay_primary_color_enable']) && !empty($values['nubay_primary_color'])) {
    nubay_themestyles_generate_style_data_primary_color($values, $styles_data);
  }
  if (!empty($values['nubay_secondary_color_enable']) && !empty($values['nubay_secondary_color'])) {
    nubay_themestyles_generate_style_data_secondary_color($values, $styles_data);
  }


  if (!empty($styles_data)) {
    $styles = implode("\n", $styles_data);
    $styles = preg_replace('/^[ \t]*[\r\n]+/m', '', $styles);
    $file_name = $theme_name . '.themestyles.css';
    $filepath = "$path/$file_name";
    file_unmanaged_save_data($styles, $filepath, FILE_EXISTS_REPLACE);
  }
  else {
    $styles = '';
    $file_name = $theme_name . '.themestyles.css';
    $filepath = "$path/$file_name";
    file_unmanaged_save_data($styles, $filepath, FILE_EXISTS_REPLACE);
  }
}

/**
 * Utility function to determine if a style should include the !important keyword
 *
 * @param $global_setting
 * @param $element
 *
 * @return bool
 */
function nubay_themestyles_do_important($global_setting, $element) {
  $important_styles_keywords = array(
    'sf-menu',
  );
  $do_important = FALSE;
  if (empty($global_setting)) {
    foreach ($important_styles_keywords as $keyword) {
      if (strpos($element, $keyword) !== FALSE) {
        $do_important = TRUE;
      }
    }
  }
  else {
    $do_important = TRUE;
  }
  return $do_important;
}

/**
 * Utility function to prepare primary colors styles data
 * 
 * @param $values
 * @param $styles_data
 */
function nubay_themestyles_generate_style_data_primary_color($values, &$styles_data) {
  // foreground
  if (!empty($values['nubay_primary_color_elements_foreground'])) {
    foreach ($values['nubay_primary_color_elements_foreground'] as $key => $value) {
      $do_important = nubay_themestyles_do_important($values['nubay_primary_color_use_important'], $key);
      $styles_data[] = $key . '{color:' . $values['nubay_primary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }
  if (!empty($values['nubay_primary_color_additional_foreground'])) {
    foreach (explode(',', $values['nubay_primary_color_additional_foreground']) as $additional_element) {
      $do_important = nubay_themestyles_do_important($values['nubay_primary_color_use_important'], $additional_element);
      $styles_data[] = trim($additional_element) . '{color:' . $values['nubay_primary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }
  // background
  if (!empty($values['nubay_primary_color_elements_background'])) {
    foreach ($values['nubay_primary_color_elements_background'] as $key => $value) {
      $do_important = nubay_themestyles_do_important($values['nubay_primary_color_use_important'], $key);
      $styles_data[] = $key . '{background:' . $values['nubay_primary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }

  if (!empty($values['nubay_primary_color_additional_background'])) {
    foreach (explode(',', $values['nubay_primary_color_additional_background']) as $additional_element) {
      $do_important = nubay_themestyles_do_important($values['nubay_primary_color_use_important'], $additional_element);
      $styles_data[] = trim($additional_element) . '{background:' . $values['nubay_primary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }
}

/**
 * Utility function to prepare secondary colors styles data
 *
 * @param $values
 * @param $styles_data
 */
function nubay_themestyles_generate_style_data_secondary_color($values, &$styles_data) {
  // foreground
  if (!empty($values['nubay_secondary_color_elements_foreground'])) {
    foreach ($values['nubay_secondary_color_elements_foreground'] as $key => $value) {
      $do_important = nubay_themestyles_do_important($values['nubay_secondary_color_use_important'], $key);
      $styles_data[] = $key . '{color:' . $values['nubay_secondary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }
  if (!empty($values['nubay_secondary_color_additional_foreground'])) {
    foreach (explode(',', $values['nubay_secondary_color_additional_foreground']) as $additional_element) {
      $do_important = nubay_themestyles_do_important($values['nubay_secondary_color_use_important'], $additional_element);
      $styles_data[] = trim($additional_element) . '{color:' . $values['nubay_secondary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }
  // background
  if (!empty($values['nubay_secondary_color_elements_background'])) {
    foreach ($values['nubay_secondary_color_elements_background'] as $key => $value) {
      $do_important = nubay_themestyles_do_important($values['nubay_secondary_color_use_important'], $key);
      $styles_data[] = $key . '{background:' . $values['nubay_secondary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }

  if (!empty($values['nubay_secondary_color_additional_background'])) {
    foreach (explode(',', $values['nubay_secondary_color_additional_background']) as $additional_element) {
      $do_important = nubay_themestyles_do_important($values['nubay_secondary_color_use_important'], $additional_element);
      $styles_data[] = trim($additional_element) . '{background:' . $values['nubay_secondary_color'] . ($do_important  ? ' !important' : '') . ';}';
    }
  }
}

/**
 * Function to add Drupal FAPI code for Inline Blocks extension
 *
 * @param $form
 * @param $form_state
 */
function nubay_inline_block_form(&$form, &$form_state) {
  // Get the active theme name, we need it at some stage.
  $theme_name = $form_state['build_info']['args'][0];

  // Get the active themes info array
  $info_array = at_get_info($theme_name);

  // Regions we don't want to include
  $unset_regions = array(
    'dashboard_main',
    'dashboard_sidebar',
    'dashboard_inactive',
    'page_bottom',
    'page_top',
    'content', // exclude the main content region
  );

  // Prepare regions
  foreach ($info_array['regions'] as $key => $value) {
    if (in_array($key, $unset_regions)) {
      unset($key);
    }
    if (isset($key)) {
      $regions[$key] = $value;
    }
  }

  $form['at']['nubay_inline_block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Inline Blocks'),
    '#description' => t('<h3>Inline Blocks</h3><p>Setting inline block styles for regions with the theme via the AT infrastructure</p>'),
  );

  // Build form elements for each region
  if (!empty($regions)) {
    foreach ($regions as $region_name => $region_label) {

      $title = check_plain($region_label);
      $region_name = check_plain($region_name);

      $form['at']['nubay_inline_block']['region-options-' . $region_name] = [
        '#type'  => 'fieldset',
        '#title' => t("Options for the $title region"),
      ];
      $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_' . $region_name] = [
        '#type'          => 'checkbox',
        '#title'         => t($title),
        '#return'        => 1,
        '#default_value' => at_get_setting('inline_block_' . $region_name),
      ];
      $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_widths_' . $region_name] = [
        '#type'   => 'fieldset',
        '#title'  => t('Block Widths'),
        '#states' => ['invisible' => ['input[name=inline_block_' . $region_name . ']' => ['checked' => FALSE]]],
      ];

      $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_widths_' . $region_name]['inline_block_' . $region_name . '_vertical_align'] = [
        '#type'          => 'select',
        '#title'         => 'Vertical Alignment',
        '#default_value' => at_get_setting('inline_block_' . $region_name . '_vertical_align'),
        '#options' => [
          '' => 'None',
          'baseline' => 'Baseline',
          'sub' => 'Sub',
          'super' => 'Super',
          'top' => 'Top',
          'text-top' => 'Text top',
          'middle' => 'Middle',
          'bottom' => 'Bottom',
          'text-bottom' => 'Text Bottom'
        ],
      ];

      for ($i = 1; $i < 7 ; $i++) {
        $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_widths_' . $region_name]['inline_block_' . $region_name . '_desktop_block_' . $i] = [
          '#type'          => 'textfield',
          '#title'         => 'Block ' . $i . ' Width',
          '#description'   => 'Enter a width with the unit, e.g 33% or 250px',
          '#default_value' => at_get_setting('inline_block_' . $region_name . '_desktop_block_' . $i),
        ];
      }

      $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_widths_' . $region_name]['inline_block_' . $region_name . '_stack_tablet_landscape'] = [
        '#type'          => 'checkbox',
        '#title'         => 'Stack blocks in tablet landscape viewport',
        '#default_value' => at_get_setting('inline_block_' . $region_name . '_stack_tablet_landscape'),
      ];
      $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_widths_' . $region_name]['inline_block_' . $region_name . '_stack_tablet_portrait'] = [
        '#type'          => 'checkbox',
        '#title'         => 'Stack blocks in tablet portrait viewports',
        '#default_value' => at_get_setting('inline_block_' . $region_name . '_stack_tablet_portrait'),
      ];
      $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_widths_' . $region_name]['inline_block_' . $region_name . '_stack_mobile_landscape'] = [
        '#type'          => 'checkbox',
        '#title'         => 'Stack blocks in mobile landscape viewports',
        '#default_value' => at_get_setting('inline_block_' . $region_name . '_stack_mobile_landscape'),
      ];
      $form['at']['nubay_inline_block']['region-options-' . $region_name]['inline_block_widths_' . $region_name]['inline_block_' . $region_name . '_stack_mobile_portrait'] = [
        '#type'          => 'checkbox',
        '#title'         => 'Stack blocks in mobile portrait viewports',
        '#default_value' => at_get_setting('inline_block_' . $region_name . '_stack_mobile_portrait'),
      ];
    }
  }
  $form['#submit'][] = 'nubay_inline_block_theme_settings_submit';
}

/**
 * Submit handler for the Inline Blocks extension settings form, generate css for inline blocks based on settings chosen
 *
 * @param $form
 * @param $form_state
 */
function nubay_inline_block_theme_settings_submit($form, $form_state) {
// Set form_state values into one variable
  $values = $form_state['values'];

  // Get the active theme name, $theme_key will return the admin theme
  $theme_name = $form_state['build_info']['args'][0];

  // Set the path variable to the right path
  if ($values['global_files_path'] === 'public_files') {
    $path = 'public://adaptivetheme/' . $theme_name . '_files';
  }
  elseif ($values['global_files_path'] === 'theme_directory') {
    $path = drupal_get_path('theme', $theme_name) . '/generated_files';
  }
  elseif ($values['global_files_path'] === 'custom_path') {
    $path = $values['custom_files_path'];
  }

  // Get the active themes info array
  $info_array = at_get_info($theme_name);

  // Regions we don't want to include
  $unset_regions = array(
    'dashboard_main',
    'dashboard_sidebar',
    'dashboard_inactive',
    'page_bottom',
    'page_top',
    'content', // exclude the main content region
  );

  // Prepare regions
  foreach ($info_array['regions'] as $key => $value) {
    if (in_array($key, $unset_regions)) {
      unset($key);
    }
    if (isset($key)) {
      $regions[$key] = $value;
    }
  }

  // $styles_data holds all data for the stylesheet
  $styles_data = [];

  // Build form elements for each region
  if (!empty($regions)) {
    foreach ($regions as $region_name => $region_label) {
      nubay_inline_block_generate_style_data($values, $region_name, $styles_data);
    }
  }

  if (!empty($styles_data)) {
    $styles = implode("\n", $styles_data);
    $styles = preg_replace('/^[ \t]*[\r\n]+/m', '', $styles);
    $file_name = $theme_name . '.inlineblock-styles.css';
    $filepath = "$path/$file_name";
    file_unmanaged_save_data($styles, $filepath, FILE_EXISTS_REPLACE);
  }
  else {
    $styles = '';
    $file_name = $theme_name . '.inlineblock-styles.css';
    $filepath = "$path/$file_name";
    file_unmanaged_save_data($styles, $filepath, FILE_EXISTS_REPLACE);
  }
}

/**
 * Utility function to populate styles_data array with css
 *
 * @param $values
 * @param $region_name
 * @param $styles_data
 */
function nubay_inline_block_generate_style_data($values, $region_name, &$styles_data) {
  if (!empty($values['inline_block_' . $region_name])) {
    // set display property to inline block for the region
    $styles_data[] = '.' . $region_name . ' .block {display:inline-block;}';
    // set vertical alignment
    if (!empty($values['inline_block_' . $region_name . '_vertical_align'])) {
      $styles_data[] = '.' . $region_name . ' .block {vertical-align:' . $values['inline_block_' . $region_name . '_vertical_align'] . ';}';
    }
    // set block widths
    for ($i = 1; $i < 7 ; $i++) {
      if (!empty($values['inline_block_' . $region_name . '_desktop_block_' . $i])) {
        $styles_data[] = '.' . $region_name . ' .block:nth-child(' . $i . ') {width:' . $values['inline_block_' . $region_name . '_desktop_block_' . $i] . ';}';
      }
    }
    // set blocks to stack for tablet/mobile
    // tablet landscape
    if (!empty($values['inline_block_' . $region_name . '_stack_tablet_landscape'])) {
      $styles_data[] = '@media ' . $values['tablet_landscape_media_query'] . ' {' . '.' . $region_name . ' .block {display:block;width:100% !important;}}';
    }
    // tablet portrait
    if (!empty($values['inline_block_' . $region_name . '_stack_tablet_portrait'])) {
      $styles_data[] = '@media ' . $values['tablet_portrait_media_query'] . ' {' . '.' . $region_name . ' .block {display:block;width:100% !important;}}';
    }
    // mobile landscape
    if (!empty($values['inline_block_' . $region_name . '_stack_mobile_landscape'])) {
      $styles_data[] = '@media ' . $values['smalltouch_landscape_media_query'] . ' {' . '.' . $region_name . ' .block {display:block;width:100% !important;}}';
    }
    // mobile portrait
    if (!empty($values['inline_block_' . $region_name . '_stack_mobile_portrait'])) {
      $styles_data[] = '@media ' . $values['smalltouch_portrait_media_query'] . ' {' . '.' . $region_name . ' .block {display:block;width:100% !important;}}';
    }
  }
}