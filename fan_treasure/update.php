<?php

include_once 'helper/api.php';
include_once 'header.php';
include_once 'style.php';

include_once 'navigation.php';

// todo check slow performance

echo "<font size=\"6\"><b>Update</b></font><br><br>";

echo "Updating standings... <br>";
updateTeams();
echo "Standings updated! <br>";
echo "Updating matches... <br>";
updateGames();
echo "Matches updated! <br>";

