import React, { useState } from 'react';
import './App.css';

const App = () => {
  const [tasks, setTasks] = useState([]);
  const [editingTaskId, setEditingTaskId] = useState(null);
  const [editedTask, setEditedTask] = useState({ name: '', description: '' });

  const handleChange = e => {
    const { name, value } = e.target;
    setEditedTask(prevTask => ({ ...prevTask, [name]: value }));
  };

  const handleEdit = () => {
    const updatedTasks = tasks.map(task =>
      task.id === editingTaskId ? { ...task, ...editedTask } : task
    );
    setTasks(updatedTasks);
    setEditingTaskId(null);
  };

  const addTask = () => {
    setTasks([...tasks, { ...editedTask, completed: false, id: Date.now() }]);
    setEditedTask({ name: '', description: '' });
  };

  const deleteTask = id => {
    const updatedTasks = tasks.filter(task => task.id !== id);
    setTasks(updatedTasks);
  };

  const toggleCompleted = id => {
    const updatedTasks = tasks.map(task =>
      task.id === id ? { ...task, completed: !task.completed } : task
    );
    setTasks(updatedTasks);
  };

  const editTask = id => {
    const taskToEdit = tasks.find(task => task.id === id);
    setEditedTask(taskToEdit);
    setEditingTaskId(id);
  };

  return (
    <div className="App">
      <h1>Task Manager</h1>
      <form onSubmit={e => { e.preventDefault(); addTask(); }}>
        <input
          type="text"
          name="name"
          value={editedTask.name}
          onChange={handleChange}
          placeholder="Task name"
        />
        <input
          type="text"
          name="description"
          value={editedTask.description}
          onChange={handleChange}
          placeholder="Task description"
        />
        <button type="submit">Add Task</button>
      </form>
      <ul>
        {tasks.map(task => (
          <li key={task.id}>
            {editingTaskId === task.id ? (
              <>
                <input
                  type="text"
                  name="name"
                  value={editedTask.name}
                  onChange={handleChange}
                  placeholder="Task name"
                />
                <input
                  type="text"
                  name="description"
                  value={editedTask.description}
                  onChange={handleChange}
                  placeholder="Task description"
                />
                <button onClick={handleEdit}>Save</button>
                <button onClick={() => setEditingTaskId(null)}>Cancel</button>
              </>
            ) : (
              <>
                <h2 onClick={() => editTask(task.id)}>{task.name}</h2>
                <p>{task.description}</p>
              </>
            )}
            <button onClick={() => toggleCompleted(task.id)}>
              {task.completed ? 'Mark Incomplete' : 'Mark Complete'}
            </button>
            <button onClick={() => deleteTask(task.id)}>Delete</button>
          </li>
        ))}
      </ul>
    </div>
  );
};

export default App;