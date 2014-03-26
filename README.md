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

This module provides a way to plug a choropleth map
(http://en.wikipedia.org/wiki/Choropleth_map) as an additional view for the
recline multiview provided with the recline module
(http://drupal.org/project/recline).

The goal is to tie a relation between a column of a recline field file
(US State Names) with the name property of Features in a
FeatureCollection within a geojson file
(http://en.wikipedia.org/wiki/GeoJSON#Example). Through that relation it
sets coloring properties for the collection of geojson geometries comparing the
values within other columns of the recline field file to a preset
(or precalculated) color scale. It also provides UI to filter the data through
Year and Category columns (if present in the data).


Requirements
------------

 * Recline (https://drupal.org/project/recline)

Installation
------------

Enable the choropleth module, either through the admin UI or with drush.


Configuration
-------------

There's no actual drupal configuration you need to set to get the
functionality provided by this module.

Usage
-----

    1. Go to the edit/add page for a node that has a recline field.
    2. Upload a csv file with a 'State' column present in the header.
    3. States Map: check the states map checkbox.
    4. (optional) Map Data: Specify the data column you are going to use as the source for
       the coloring. If the administrator does not provide
       one, UI to select the column will be provided for the user (if there's
       more than one column available).
    5. (optional) Breakpoints: Specify a set of breakpoints separated by commas to be the
       color scale. e.g: 10%, 20, 50%, 100, 500. If the
       administrator does not provide this, the system will precalculated a set
       based on the data.
    6. (optional) Color Scale: Specify one of the provided color scales for the polygons.
       There is a default in place if the administrator does not provide this.
    7. Save and enjoy your choropleth map!


Todo's
------

 * Extend the recline module to provide a pluggable way of attaching third
   party Recline.js Views (like the one provided by this module).
 * Split the Recline.js View to a separate git repository and attach the code
   using hook_library_info().
 * Initialize all the contrib js with hook_library_info().
 * Provide admin configuration pages to upload additional polygon source data
   and ways to map it to a set of column names. e.g: upload world map polygons
   and set the file to tie it to a Country column.
 * Provide UI to reset the color scale breakpoints to the end user.
 * Extend the filtering capabilities to any column within the data that does
   not contain numerical data (not just year and category).


Contrib js Libraries
--------------------

Contrib Libraries used:

 * chroma.js for the coloring -> https://github.com/gka/chroma.js
 * numeral.js for the number formatting -> http://numeraljs.com

