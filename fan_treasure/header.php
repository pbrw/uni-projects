<?php
// prints choosen team and city
// allows to modify it

echo '<div class="enjoy-css">';
include_once 'helper/accessors.php';
include_once 'style.php';

$myTeamId = getMyTeamId();
$myCityId = getMyCityId();

printMyTeam($myTeamId);
askForMyTeam($myCityId);
echo "<br>";
printMyCity($myCityId);
askForMyCity($myTeamId);

function printMyTeam($myTeamId) {
    $html = 'My Team is: ';

    if ($myTeamId != -1) {
        $teamsNames = getTeamsNames();
        $html .= $teamsNames[$myTeamId] . '<br>';
    }
    else {
        $html .= 'Not selected<br>';
    }

    echo $html;
}

function askForMyTeam($myCityId) {
    $file = $_SERVER['PHP_SELF'];
    $action = '"' . $file . '?myCityId=' . $myCityId . '"';
    $html = '<form action=' . $action . 'method="get"> <select name="myTeamId" class="select-style">';

    $teams = getTeams();
    $myTeamId = getMyTeamId();

    $html .= '<option value=-1 ';
    if ($myTeamId == -1) $html .= 'SELECTED';
    $html .= '> none </option>';

    foreach ($teams as $key => $value) {
        $html .= '<option value=' . $value['team_id'];
        if ($value['team_id'] == $myTeamId) $html .= ' SELECTED';
        $html .= '>' . htmlspecialchars($value['name']) . '</option>';
    }

    $html .= '</select> <input type="submit" class="myButton" value="Select" /> <br>';

    echo $html;
}

function printMyCity($myCityId) {
    $html = 'My City is: ';

    if ($myCityId != -1) {
        $citiesNames = getCitiesNames();
        $html .= $citiesNames[$myCityId] . '<br>';
    }
    else {
        $html .= 'Not selected<br>';
    }

    echo $html;
}

function askForMyCity($myTeamId) {
    $html = '<select name="myCityId" class="select-style">';
    $cities = getCities();

    $myCityId = getMyCityId();

    $html .= '<option value=-1 ';
    if ($myCityId == -1) $html .= 'SELECTED';
    $html .= '> none </option>';

    foreach ($cities as $key => $value) {
        $html .= '<option value='.$value['city_id'];
        if ($value['city_id'] == $myCityId) $html .= ' SELECTED';
        $html .= '>'. htmlspecialchars($value['name']) . '</option>';
    }



    $html .= '</select> <input type="submit" class="myButton" value="Select" /> </form>';

    echo $html;
}




