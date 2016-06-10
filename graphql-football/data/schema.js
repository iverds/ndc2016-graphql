import {
  GraphQLSchema,
  GraphQLObjectType,
  GraphQLString,
  GraphQLList,
  GraphQLInt,
  GraphQLID,
} from 'graphql';


import { getPlayers, getTeams } from './database';

const teamType = new GraphQLObjectType({
  name: 'Team',
  fields: () => ({
    name: { type: GraphQLString },
  }),
});

const playerType = new GraphQLObjectType({
  name: 'Player',
  fields: () => ({
    id: { type: GraphQLID },
    name: { type: GraphQLString },
    dateofbirth: { type: GraphQLString },
    teams: {
      type: new GraphQLList(teamType),
      resolve: (player) => getTeams().filter(p => player.teams.indexOf(p.id) > -1) },
  }),
});

export const schema = new GraphQLSchema({
  query: new GraphQLObjectType({
    name: 'Query',
    fields: () => ({
      players: {
        type: new GraphQLList(playerType),
        description: 'List of players',
        args: {
          top: { type: GraphQLInt, description: 'Gets the given top elements' },
        },
        resolve: (_, args) => getPlayers(args),
      },
      teams: {
        type: new GraphQLList(teamType),
        description: 'List of teams',
        resolve: () => getTeams(),
      },
    }),
  }),
});
