CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Usage
 * Todo's
 * Contrib js Libraries


Introduction
------------

This module provides a choropleth map (http://en.wikipedia.org/wiki/Choropleth_map)
view for the the recline field provided by recline module (http://drupal.org/project/recline).

It ties a field in the uploaded file (i.e. state) to shapes provided by a
GeoJSON file (http://en.wikipedia.org/wiki/GeoJSON#Example). Then it colors
those shapes by comparing values in a second field (e.g. number of drug related
deaths). It also provides UI to interactively filter the data through Year and
Category columns (if present in the data).

It was originally built to extend display options provided by the DKAN Drupal
Distribution, to be embedded in other websites. See live examples here:

 - http://www.whitehouse.gov/raise-the-wage
 - http://maproom.whitehouse.gov/choropleth-map/86
 - http://maproom.whitehouse.gov/choropleth-map/146


Requirements
------------

 * Recline (https://drupal.org/project/recline)


Installation
------------

Enable the choropleth module, either through the admin UI or with drush.


Configuration
-------------

There's no actual Drupal configuration you need to set to get the
functionality provided by this module.


Usage
-----

    1. Go to the edit/add page for a node that has a recline field (e.g. in DKAN
       add/edit a "resource" node).
    2. Upload a CSV file with a 'State' column present in the header.
    3. States Map: Check the states map checkbox.
    4. (optional) Map Data: Specify the data column you are going to use as the source for
       the coloring. If the administrator does not provide one, UI to select the
       column will be provided for the end-user (if there's more than one column available).
    5. (optional) Color Breakpoints: Specify a set of breakpoints separated by commas to be the
       color scale. e.g: 10, 20, 50, 100, 500. If the administrator does not
       provide this, the system will generate its own color breakpoints.
    6. (optional) Color Scale: Specify one of the provided color scales for the polygons.
    7. Save and enjoy your choropleth map!


Contrib js Libraries
--------------------

Contrib Libraries used:

 * chroma.js for the coloring -> https://github.com/gka/chroma.js
 * numeral.js for the number formatting -> http://numeraljs.com
