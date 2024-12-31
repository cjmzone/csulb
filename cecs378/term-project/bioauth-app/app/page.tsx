'use client';

import { useState } from 'react';
import { startRegistration } from '@simplewebauthn/browser';

export default function Home() {
  const [username, setUsername] = useState('');
  const [message, setMessage] = useState('');

  const handleRegister = async () => {
    try {
      // Step 1: Fetch registration options
      const optionsRes = await fetch('/api/auth/register', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username }),
      });

      const options = await optionsRes.json();

      // Step 2: Perform registration
      const attestationResponse = await startRegistration(options);

      // Step 3: Verify registration
      const verificationRes = await fetch('/api/auth/register', {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username, response: attestationResponse }),
      });

      const verification = await verificationRes.json();
      setMessage(verification.verified ? 'Registration successful!' : 'Registration failed.');
    } catch (error) {
      console.error(error);
      setMessage('An error occurred during registration.');
    }
  };

  return (
    <div style={{ padding: '20px' }}>
      <h1>BioAuthentication with WebAuthn</h1>
      <input
        type="text"
        placeholder="Enter your username"
        value={username}
        onChange={(e) => setUsername(e.target.value)}
        style={{ marginRight: '10px' }}
      />
      <button onClick={handleRegister}>Register</button>
      <p>{message}</p>
    </div>
  );
}
