import 'babel-polyfill';

// import App from './components/App';
import AppHomeRoute from './routes/AppHomeRoute';
import React from 'react';
import ReactDOM from 'react-dom';
import Relay from 'react-relay';
import UserStore from './components/UserStore';

ReactDOM.render(
  <Relay.RootContainer
    Component={UserStore}
    route={new AppHomeRoute()}
  />,
  document.getElementById('root')
);
