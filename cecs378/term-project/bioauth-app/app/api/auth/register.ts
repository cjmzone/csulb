import { NextResponse } from 'next/server';
import { generateRegistrationOptions, verifyRegistrationResponse } from '@simplewebauthn/server';

let userStorage: Record<string, any> = {}; // Temporary user storage

export async function POST(request: Request) {
  const { username } = await request.json();

  const user = {
    id: new TextEncoder().encode(username), // Converts string to Uint8Array
    username,
  };
  userStorage[username] = user;

  const options = await generateRegistrationOptions({
    rpName: 'BioAuth App',
    rpID: 'localhost',
    userID: user.id,
    userName: user.username,
  });

  userStorage[username].challenge = options.challenge;
  return NextResponse.json(options);
}

export async function PUT(request: Request) {
  const { username, response } = await request.json();
  const user = userStorage[username];

  const verification = await verifyRegistrationResponse({
    response,
    expectedChallenge: user.challenge,
    expectedOrigin: 'http://localhost:3000',
    expectedRPID: 'localhost',
  });

  if (verification.verified) {
    user.authenticator = verification.registrationInfo;
    return NextResponse.json({ verified: true });
  } else {
    return NextResponse.json({ verified: false });
  }
}
