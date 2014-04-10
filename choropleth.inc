<?php

/**
 * @file
 * Non-hook implementations for the Choropleth module.
 */

/**
 * Returns a simple csv with states mapped to GeoJson shapes.
 */
function choropleth_usstates_geojson() {
  $module_path = drupal_get_path('module', 'choropleth');
  $filename = 'states_geojson.json';
  $filepath = $module_path . '/data/' . $filename;
  $file_contents = json_decode(file_get_contents($filepath));
  $state_geometry = $file_contents;

  $state_abbreviations = array_flip(choropleth_get_usstate_abbr());
  $state_geojson = array();
  foreach ($state_geometry->features as $state) {
    $state_name = $state->properties->name;
    if (!empty($state_abbreviations[$state_name])) {
      $state_abbreviation = $state_abbreviations[$state_name];
      $state_geojson[$state_abbreviation] = array(
        'name' => $state_name,
        'geojson' => json_encode($state->geometry),
      );
    }
  }

  // Add the headers needed to let the browser know this is a csv file download.
  drupal_add_http_header('Content-Type', 'text/csv; utf-8');
  drupal_add_http_header('Content-Disposition', 'attachment; filename = usstates_geojson.csv');

  // Instead of writing to a file, we write to the output stream.
  $fh = fopen('php://output', 'w');

  // Add a header row.
  fputcsv($fh, array(t('State'), t('Geometry')));

  // Loop through rows and write the csv data.
  foreach ($state_geojson as $line) {
    fputcsv($fh, $line);
  }

  // Close the output stream.
  fclose($fh);

}

/**
 * Returns an associative array of US state mapped to full names.
 *
 * @return array
 *   Associative array of US state mapped to full names.
 */
function choropleth_get_usstate_abbr() {
  return array(
    'AL' => 'Alabama',
    'AK' => 'Alaska',
    'AZ' => 'Arizona',
    'AR' => 'Arkansas',
    'CA' => 'California',
    'CO' => 'Colorado',
    'CT' => 'Connecticut',
    'DE' => 'Delaware',
    'DC' => 'District of Columbia',
    'FL' => 'Florida',
    'GA' => 'Georgia',
    'HI' => 'Hawaii',
    'ID' => 'Idaho',
    'IL' => 'Illinois',
    'IN' => 'Indiana',
    'IA' => 'Iowa',
    'KS' => 'Kansas',
    'KY' => 'Kentucky',
    'LA' => 'Louisiana',
    'ME' => 'Maine',
    'MD' => 'Maryland',
    'MA' => 'Massachusetts',
    'MI' => 'Michigan',
    'MN' => 'Minnesota',
    'MS' => 'Mississippi',
    'MO' => 'Missouri',
    'MT' => 'Montana',
    'NE' => 'Nebraska',
    'NV' => 'Nevada',
    'NH' => 'New Hampshire',
    'NJ' => 'New Jersey',
    'NM' => 'New Mexico',
    'NY' => 'New York',
    'NC' => 'North Carolina',
    'ND' => 'North Dakota',
    'OH' => 'Ohio',
    'OK' => 'Oklahoma',
    'OR' => 'Oregon',
    'PA' => 'Pennsylvania',
    'RI' => 'Rhode Island',
    'SC' => 'South Carolina',
    'SD' => 'South Dakota',
    'TN' => 'Tennessee',
    'TX' => 'Texas',
    'UT' => 'Utah',
    'VT' => 'Vermont',
    'VA' => 'Virginia',
    'WA' => 'Washington',
    'WV' => 'West Virginia',
    'WI' => 'Wisconsin',
    'WY' => 'Wyoming',
  );
}

/**
 * Returns an array of Color Scales for the map.
 *
 * @return array
 *   array of Color Scales for the map.
 */
function choropleth_color_scale_settings() {
  return array(
    'Canyons' => array('#ffffcc', '#ffeda0', '#fed976', '#feb24c', '#fd8d3c', '#fc4e2a', '#e31a1c', '#bd0026', '#800026'),
    'Fire' => array('#ffffe5', '#fff7bc', '#fee391', '#fec44f', '#fe9929', '#ec7014', '#cc4c02', '#993404', '#662506'),
    'Beach' => array('#ffffd9', '#edf8b1', '#c7e9b4', '#7fcdbb', '#41b6c4', '#1d91c0', '#225ea8', '#253494', '#081d58'),
    'Money' => array('#ffffe5', '#f7fcb9', '#d9f0a3', '#addd8e', '#78c679', '#41ab5d', '#238443', '#006837', '#004529'),
    'Flora' => array('#fff7f3', '#fde0dd', '#fcc5c0', '#fa9fb5', '#f768a1', '#dd3497', '#ae017e', '#7a0177', '#49006a'),
    'Princess' => array('#f7f4f9', '#e7e1ef', '#d4b9da', '#c994c7', '#df65b0', '#e7298a', '#ce1256', '#980043', '#67001f'),
    'Emotive' => array('#fff7fb', '#ece2f0', '#d0d1e6', '#a6bddb', '#67a9cf', '#3690c0', '#02818a', '#016c59', '#014636'),
    'Breeze' => array('#fff7fb', '#ece7f2', '#d0d1e6', '#a6bddb', '#74a9cf', '#3690c0', '#0570b0', '#045a8d', '#023858'),
    'Burnt' => array('#fff7ec', '#fee8c8', '#fdd49e', '#fdbb84', '#fc8d59', '#ef6548', '#d7301f', '#b30000', '#7f0000'),
    'Aqua' => array('#f7fcf0', '#e0f3db', '#ccebc5', '#a8ddb5', '#7bccc4', '#4eb3d3', '#2b8cbe', '#0868ac', '#084081'),
    'Regal' => array('#f7fcfd', '#e0ecf4', '#bfd3e6', '#9ebcda', '#8c96c6', '#8c6bb1', '#88419d', '#810f7c', '#4d004b'),
    'Taiga' => array('#f7fcfd', '#e5f5f9', '#ccece6', '#99d8c9', '#66c2a4', '#41ae76', '#238b45', '#006d2c', '#00441b'),
    'WH Blue Range' => array('#daecff', '#c9e4ff', '#9bcdff', '#71b8ff', '#42a1ff', '#2187eb', '#0069d1', '#004f9d', '#003366'),
    'WH Teal Range' => array('#c7eeec', '#b0e6e4', '#96dadb', '#85d1d2', '#72c3c6', '#5eb0bc', '#4293a7', '#3d80a3', '#336699'),
    'WH Orange Range' => array('#ffe7b0', '#ffdf94', '#ffd77a', '#ffd165', '#ffc94a', '#ffc231', '#f4b010', '#e6a201', '#d29400'),
    'WH Red Range' => array('#feb3b3', '#fa9d9d', '#f18282', '#e86a6a', '#e05353', '#d54040', '#c62f2f', '#a40e0e', '#7f0000'),
    'WH Grey Range' => array('#cccccc', '#b7b7b7', '#a8a8a8', '#959595', '#7d7d7d', '#707070', '#626262', '#484848', '#333333'),
    'WH Black to Blue' => array('#0e0029', '#15024b', '#11026a', '#05137c', '#13269a', '#1d3da6', '#2451ad', '#2c60b4', '#3376b8'),
    'WH Blue to Black' => array('#3376b8', '#2c60b4', '#2451ad', '#1d3da6', '#13269a', '#05137c', '#11026a', '#15024b', '#0e0029'),
    'WH Green to Grey' => array('#5e8d00', '#567715', '#4e6424', '#4b5832', '#434938', '#3e3f3c', '#323232', '#262626', '#131313'),
    'WH Blue to Grey' => array('#3376b8', '#4473a1', '#506e8b', '#596775', '#53585e', '#48494b', '#3d3d3d', '#2c2c2c', '#131313'),
    'WH Red to Grey' => array('#880000', '#781919', '#722929', '#613434', '#543939', '#433636', '#3c3838', '#2b2929', '#131313'),
    'WH Grey to Red' => array('#131313', '#2b2929', '#3c3838', '#433636', '#543939', '#613434', '#722929', '#781919', '#880000'),
    'WH Blue to Red' => array('#3376b8', '#6185c5', '#7e86d2', '#ac97dd', '#cf97d9', '#d075b1', '#c25780', '#bc3444', '#a60000'),
    'WH Red to Blue' => array('#a60000', '#bc3444', '#c25780', '#d075b1', '#cf97d9', '#ac97dd', '#7e86d2', '#6185c5', '#3376b8'),
  );
}

/**
 * Returns an array of options for the color scale select on the admin.
 *
 * @return array
 *   array of options for the color scale select on the admin.
 */
function choropleth_color_scale_tableselect_options() {
  $settings = choropleth_color_scale_settings();
  $output = array();
  foreach ($settings as $key => $colors) {
    $output[] = array(
      'name' => $key,
      'colors' => theme('choropleth-color-scale-option', array('colors' => $colors)),
    );
  }
  return $output;
}

/**
 * Generate the help text html.
 *
 * @return string
 *   Html of help list text.
 */
function choropleth_help_text() {
  $geolocation_text = t('Will cause the data to be displayed as pins on the map and not shown as an option in the category dropdown.');
  $help_items = array(
    '0' => array(
      'data' => t('Any column to be displayed on a choropleth map (ie. state-by-state map) should have units specified in the header for that column.  Example: <em>Population Density (people / sq. mile)</em>'),
    ),
    '1' => array(
      'data' => 'Special columns: If the following columns are present in your data then they will be used to build the choropleth map:',
      'children' => array(
        array('data' => 'state OR states - ' . t('Will trigger a state-by-state choropleth map using the overlay regions for each state.')),
        array('data' => 'year - ' . t("Enable users to select from a dropdown list of available years' data to view on the map.")),
        array('data' => 'categories - ' . t('Enable users to filter data for a particular category.')),
        array('data' => 'popup text - ' . t('Will display this text in a pop up bubble when a region is clicked.')),
        array('data' => 'popup link - ' . t('Will display a clickable link to the url provided. Example:') . ' <em>http://some-website.com</em>'),
        array('data' => 'popup link text - ' . t('Will use this text as the visible portion of the link if provided.  Example:') . ' <em>' . t('Read More') . '</em>'),
        array('data' => 'latitude (lat) AND longitude (lon)- ' . $geolocation_text . ' ' . t("Both lat and lon or latitude and longitude columns need to be present.")),
      ),
    ),

  );
  return theme('item_list', array('items' => $help_items));
}
