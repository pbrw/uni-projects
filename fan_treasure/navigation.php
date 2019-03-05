<?php
// contains links to other subsites

include_once 'helper/accessors.php';
include_once 'style.php';

$myCityId = getMyCityId();
$myTeamId = getMyTeamId();
echo '<nav class="cl-effect-10">';
echo '
<body link="#000000" vlink="#000000" alink="#000000"> ';
printLink("home", $myCityId, $myTeamId);
printSpaces();
printLink("standings", $myCityId, $myTeamId);
printSpaces();
printLink("games", $myCityId, $myTeamId);
printSpaces();
printLink("teams", $myCityId, $myTeamId);
printSpaces();
printLink("update", $myCityId, $myTeamId);
echo '</nav>';
echo '==============================================';
echo '<br><br>';

function printLink($subsite, $myCityId, $myTeamId) {
    $html = '<a href="' . $subsite . '.php?myTeamId='. $myTeamId . '&myCityId=' . $myCityId . '">' . $subsite . '</a>';

    echo $html;
}

function printSpaces() {
    $html = ' &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';

    echo $html;
}