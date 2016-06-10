import React from 'react';
import Relay from 'react-relay';
import User from './user';

class UserStore extends React.Component {
  render() {
    return (
        <ul>
            { this.props.store.users.map(user => <User key={user.__dataID__} user={user} />)}
        </ul>
    );
  }
}

UserStore.propTypes = {
  store: React.PropTypes.object,
};

UserStore = Relay.createContainer(UserStore, {
  fragments: {
    store: () => Relay.QL`
      fragment on Store {
        users { ${User.getFragment('user')} },
      }
    `,
  },
});

export default UserStore;
