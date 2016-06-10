const players = {
  1: {
    id: '1',
    dateofbirth: '13.08.1970',
    name: 'Alan Shearer',
    teams: ['1'],
  },
  2: {
    id: '2',
    dateofbirth: '20.10.1961',
    name: 'Ian Rush',
    teams: ['2', '3'],
  },
};

const teams = {
  1: {
    id: '1',
    name: 'Newcastle',
  },
  2: {
    id: '2',
    name: 'Liverpool FC',
  },
  3: {
    id: '3',
    name: 'Juventus',
  },
};


export const getPlayers = (args) => Object.keys(players)
  .map(k => players[k])
  .slice(0, args.top || Object.keys(players).length);
  // .filter(k => !Object.keys(args).length || k.name.indexOf(args.name) > -1);
export const getById = (id) => players[id];
export const getTeamById = (id) => teams[id];
export const getTeams = () => Object.keys(teams).map(t => teams[t]);
