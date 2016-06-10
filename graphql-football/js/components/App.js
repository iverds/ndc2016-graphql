import React from 'react';
import Relay from 'react-relay';

class App extends React.Component {
  render() {
    return (
      <div>
        <h1>User list</h1>
        <ul>
          {this.props.users.map(user =>
            <li key={user.id}>{user.name} (Age: {user.age})</li>
          )}
        </ul>
      </div>
    );
  }
}

App.propTypes = {
  users: React.PropTypes.object,
};

export default Relay.createContainer(App, {
  fragments: {
    users: () => Relay.QL`
      fragment on User {
          id,
          age,
          name
      }
    `,
  },
});
