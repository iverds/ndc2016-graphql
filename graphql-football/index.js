import express from 'express';
import graphqlHTTP from 'express-graphql';

import { schema } from './data/schema';

const GRAPHQL_PORT = 8080;

const graphQLapp = express();

graphQLapp.use('/', graphqlHTTP({ schema, graphiql: true }));
graphQLapp.listen(GRAPHQL_PORT, () => {console.log(`Running graphql server on ${GRAPHQL_PORT}`);});
