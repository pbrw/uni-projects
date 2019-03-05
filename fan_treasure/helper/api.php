<?php

include_once 'database.php';

function askApi($query) {
    $token = 'b50a4512029744bc85076e3e9267dadb';
    $uri = 'http://api.football-data.org/v2/competitions/PL/' . $query;
    $reqPrefs['http']['method'] = 'GET';
    $reqPrefs['http']['header'] = 'X-Auth-Token: ' . $token;
    $stream_context = stream_context_create($reqPrefs);
    $response = file_get_contents($uri, false, $stream_context);
    return json_decode($response);
}

function updateTeams() {
    $all = askApi('standings/');
    $standings = ($all->standings[0]);
    $table = $standings->table;
    $teamsNumber = count($table);
    $conn = connect();
    for ($i = 0; $i < $teamsNumber; $i++) {
        $team = $table[$i];
        $team_id = $team->team->id;
        $points = $team->points;
        $wins = $team->won;
        $loses = $team->lost;
        $draws = $team->draw;
        $goals_for = $team->goalsFor;
        $goals_against = $team->goalsAgainst;

        $sql = "UPDATE Teams SET ";
        $sql .= 'points = ' . $points .
                ', wins = ' . $wins .
                ', loses = ' . $loses .
                ', draws = ' . $draws .
                ', goals_for = ' . $goals_for .
                ', goals_against = ' . $goals_against . ' ';
        $sql .= 'WHERE team_id = ' . $team_id . ';';

        voidQueryDatabase($conn, $sql);
    }
}

function updateGames() {
    $all = askApi('matches/');
    $matches = $all->matches;
    $matchesNumber = count($matches);
    $conn = connect();
    for ($i = 0; $i < $matchesNumber; $i++) {
        $match = $matches[$i];
        $score = $match->score;

        $sql = "UPDATE Games SET ";
        if ($score->fullTime->homeTeam === null)
            $score->fullTime->homeTeam = 'null';
        if ($score->fullTime->awayTeam === null)
            $score->fullTime->awayTeam = 'null';
        
        $sql .= 'score1 = ' . $score->fullTime->homeTeam .
            ', score2 = ' . $score->fullTime->awayTeam;
        $sql .= ' WHERE game_id = ' . $match->id . ';';
        voidQueryDatabase($conn, $sql);
    }
}