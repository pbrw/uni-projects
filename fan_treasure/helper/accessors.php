<?php

function isPost($name) {
    if ($_POST[$name]) 
        return true;
    else 
        return false;
}

function getPost($name) {
    return $_POST[$name];
}

function isGet($name) {
    if ($_GET[$name]) 
        return true;
    else 
        return false;
}

function getGet($name) {
    return $_GET[$name];
}

function getMyInt($name) {
    if (isPost($name))
        return getPost($name);

    if (isGet($name))
        return getGet($name);

    return -1;
}

function getMyString($name) {
    if (isPost($name))
        return getPost($name);

    if (isGet($name))
        return getGet($name);

    return 'none';
}

function getMyCityId() {
    return getMyInt('myCityId');
}

function getMyTeamId() {
    return getMyInt('myTeamId');
}

function getSortName() {
    $result = getMyString('sortName');
    if ($result == 'none') $result = 'position';
    return $result;
}

function getSelectedTeam() {
    $result = getMyInt('selectedTeam');
    if ($result == -1) $result = 57;
    return $result;
}

include_once 'database.php';

function getTeams() {
    return getFullTable('Teams');
}

function getTeamsNumber() {
    return count(getTeams());
}

function getTeamsNames() {
    $teams = getTeams();
    foreach ($teams as $key => $value) {
        $teams[$value['team_id']] = $value['name'];
    }
    return $teams;
}

function getPositions() {
    return getFullTable('Positions');
}

function getTeamsPositions() {
    $positions = getPositions();
    $result = array();
    foreach ($positions as $key => $value) {
        $result[$value['team_id']] = $value['position'];
    }
    return $result;
}

function getCities() {
    return getFullTable('Cities');
}

function getCitiesNumber() {
    return count(getCities());
}

function getCitiesNames() {
    $cities = getCities();
    $result = array();
    foreach ($cities as $key => $value) {
        $result[$value['city_id']] = $value['name'];
    }
    return $result;
}

function getGamesWhere($condition) {
    $columns = ['round',
                'Games.host_id',
                'h.name as host',
                'Games.guest_id',
                'g.name as guest',
                'date',
                'score1',
                'score2',
                'h.city_id as city_id'];

    $table = 'Games JOIN Teams as h ON Games.host_id = h.team_id
                    JOIN Teams as g ON Games.guest_id = g.team_id';
    $table .= ' WHERE ' . $condition;

    return getTable($table, $columns);
}

function getCitiesCoordinates() {
    $cities = getCities();
    $result = array();
    foreach ($cities as $key => $value) {
        $result[$value['city_id']] = [$value['latitude'], $value['longitude']];
    }
    return $result;
}

function getDistances() {
    return getTable('Distance', ['city1', 'city2', 'distance']);
}

function getCitiesDistances() {
    $distances = getDistances();
    $distancesNumber = count($distances);
//    print_r($distances);
    $result = array();
    for ($i = 0; $i < $distancesNumber; $i++) {
        $result[$distances[$i]['city1']][$distances[$i]['city2']] = $distances[$i]['distance'];
    }

    return $result;
}

function getDistanceBetweenPoints($lat1, $lon1, $lat2, $lon2) {
    $dist = file_get_contents("http://hisone.iscute.ovh/find_distance?lat1=".$lat1."&lon1=".$lon1."&lat2=".$lat2."&lon2=".$lon2);
    return $dist;
}

function getDistance($city1, $city2) {
    $citiesCoordinates = getCitiesCoordinates();
    return getDistanceBetweenPoints($citiesCoordinates[$city1][0],
                                    $citiesCoordinates[$city1][1],
                                    $citiesCoordinates[$city2][0],
                                    $citiesCoordinates[$city2][1]);
}

function getTeamRow($team) {
    $columns = ['t.name',
        'c.name as city',
        'l.name as league',
        't.points',
        't.wins',
        't.loses',
        't.draws',
        't.goals_for',
        't.goals_against',
        't.goals_for - goals_against as diff'];

    $tableName = 'Teams as t JOIN Leagues as l ON t.league_id = l.league_id
                    JOIN Cities as c ON t.city_id = c.city_id
                    WHERE t.team_id = ' . $team;

    return getTable($tableName, $columns);
}

function getRoundNumber() {
    $result = getMyInt('roundNumber');
    if ($result == -1) $result = 1;
    return $result;
}